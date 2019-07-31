#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<assert.h>

/*线程池里所有运行和等待的任务都是一个 cthread_worker,
 * 由于所有任务都在链表里,所以使用链表结构*/

void *myprocess(void *arg);
void pool_init(int max_thread_num);
void pool_add_worker(void *(*process)(void *arg),void *arg);
int pool_destroy();
void *thread_routine(void *arg);


typedef struct worker
{
	//回调函数,任务运行时会调用此函数
	void *(*process) (void *arg);  //结构体中函数
	void *arg; //回调函数
	struct worker *next;
}CThread_worker;

//线程池结构
typedef struct
{
	//初始化锁和变量
	pthread_mutex_t queue_lock;
	pthread_cond_t queue_ready;
	
	//链表结构,线程池中 所有等待任务
	CThread_worker *queue_head;

	//是否 销毁线程池
	int shutdown;
	pthread_t *threadid;
	//线程中允许的活动线程数目
	int max_thread_num;
	//当前等待队列的任务数目
	int cur_queue_size;
}CThread_pool;

static CThread_pool *pool = NULL;

void pool_init(int max_thread_num)
{
	pool = (CThread_pool *)malloc(sizeof(CThread_pool));
	//初始化 一个锁
	pthread_mutex_init(&(pool->queue_lock),NULL);
	//初始化 一个条件变量
	pthread_cond_init(&(pool->queue_ready),NULL);
	pool->max_thread_num = max_thread_num;
	pool->cur_queue_size = 0;

	pool->shutdown = 0;
	
	pool->threadid = (pthread_t *)malloc(sizeof(pthread_t)*max_thread_num);
	int i = 0;
	for(i = 0;i < max_thread_num;i++)   pthread_create(&(pool->threadid[i]),NULL,thread_routine,NULL);

}

void pool_add_worker(void *(*process)(void *arg),void *arg)
{
	//构造一个新任务
	CThread_worker *newworker = (CThread_worker *)malloc(sizeof(CThread_worker));
	newworker->process = process;
	newworker->arg = arg;
	newworker->next = NULL;

	pthread_mutex_lock(&(pool->queue_lock)); //加锁
	//将任务加入等待队列
	CThread_worker *member = pool->queue_head;  //将新任务加入到链表的尾部
	
	//遍历到链表的尾部
	if(member != NULL)
	{
		while(member->next != NULL)   member = member->next;  //找到尾部

		//将新任务加到member 后面
		member->next = newworker;
	}
	else 
	{
		//如果工作链表为空
		pool->queue_head = newworker;
	}

	assert(pool->queue_head != NULL);

	pool->cur_queue_size++;  //等待工作长度 加1
	pthread_mutex_unlock(&(pool->queue_lock));  //解锁
	//等待队列中有任务了,唤醒一个等待线程
	//注意 : 如果所有线程都在忙碌,这条语句不起作用
	
	pthread_cond_signal(&(pool->queue_ready));


}

int pool_destroy()
{
	if(pool->shutdown)   return -1;   //防止两次调用

	//唤醒所有等待线程,线程池要被销毁了 
	pthread_cond_broadcast(&(pool->queue_ready));

	//阻塞等待线程退出,否则就变成僵尸进程
	int i;
	for(i = 0;i < pool->max_thread_num;i++)
	{
		pthread_join(pool->threadid[i],NULL);
	}
	free(pool->threadid);

	//销毁等待队列
	CThread_worker *head = NULL;
	while(pool->queue_head != NULL)
	{
		head = pool->queue_head;
		pool->queue_head = pool->queue_head->next;
		free(head);
	}

	//条件变量 和互斥量也别忘了销毁
	pthread_mutex_destroy(&(pool->queue_lock));
	pthread_cond_destroy(&(pool->queue_ready));

	free(pool);   //销毁后指针是个好习惯
	pool = NULL;
	return 0;
}
void *thread_routine(void *arg)
{
	printf( "starting thread %lu\n",pthread_self());

	while(1)
	{
		pthread_mutex_lock(&(pool->queue_lock));
		//如果等待队列为 0且不销毁线程池,则处于阻塞状态,
		//注意 pthread_cond_wait(),是一个原子操作,等待前会解锁,唤醒后会加锁
		while(pool->cur_queue_size == 0 && !pool->shutdown)
		{
			printf("thread %lu is waiting\n",pthread_self());
			pthread_cond_wait(&(pool->queue_ready),&(pool->queue_lock));
		}

		//销毁线程池,将每个线程退出
		if(pool->shutdown)
		{
			//遇到break,continue,return,等跳转语句,千万不要忘记先解锁
			pthread_mutex_unlock(&(pool->queue_lock));

			printf( "thread %lu will exit\n",pthread_self());
			pthread_exit(NULL);
		}

		printf("thread %lu is starting to work\n",pthread_self());

		//assert 用来调试
		assert(pool->cur_queue_size != 0);
		assert(pool->queue_head != NULL);

		//等待队列长度 减1,并取出链表中的头元素
		pool->cur_queue_size--;
		CThread_worker * worker = pool->queue_head;
		pool->queue_head = worker->next;  //工作链表长度 减 1

		pthread_mutex_unlock(&(pool->queue_lock));

		//调用回调 函数,执行任务
		(*(worker->process))(worker->arg);
		free(worker);
		worker = NULL;
	}

	//这一句应该是不可达的
	pthread_exit(NULL);
}

void *myprocess(void *arg)
{
	printf( "thread is %lu,working on task %d\n",pthread_self(),*(int *)arg);
	sleep(1); //休息1 秒
	return NULL;
}
int main(int argc,char ** argv)
{
	pool_init(3);   //线程池中最多三个活动线程
	
	//连续向池中 投入 10 个任务
	int *workingnum = (int *)malloc(sizeof(int)*10);
	int i;
	for(i = 0;i < 10;i++)
	{
		workingnum[i] = i;
		pool_add_worker(myprocess,&workingnum[i]);
	}

	//等待所有任务完成
	sleep(5);
	pool_destroy();

	free(workingnum);

	return 0;
}
