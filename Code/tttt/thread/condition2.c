#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<pthread.h>

//节点结构
typedef struct node
{
	int data;
	struct node *next;
}Node;

//永远指向链表头部的指针
Node *head = NULL;
//线程同步 互斥所
pthread_mutex_t mutex;
//阻塞线程 --条件变量类型的变量
pthread_cond_t cond;

//生产者
void *producer(void *arg)
{
	while(1)
	{
		//创建一个链表的结点
		Node*pnew = (Node *)malloc(sizeof(Node));
		//结点的初始化
		pnew->data = rand() %1000;

		//使用互斥锁保护共享数据
		pthread_mutex_lock(&mutex);
		//指针域
		pnew->next = head;
		head = pnew;
		printf( "======producer:%lu,%d\n",pthread_self(),pnew->data);
		pthread_mutex_unlock(&mutex);

		//通知阻塞的消费者线程解除阻塞

		pthread_cond_signal(&cond);

		sleep(rand()%3);
	}
	return NULL;
}

//消费者
void *customer(void *arg)
{

	while(1)
	{
		pthread_mutex_lock(&mutex);
		//判断链表是否为空
		if(head == NULL)
		{
			//阻塞线程
			//该函数会对互斥锁解锁
			pthread_cond_wait(&cond,&mutex);
			//解除阻塞之后会对互斥锁进行加锁操作
		}

		//链表不为空,删掉一个结点  --删除头结点
		Node * pdel = head;
		head = head->next;

		printf( "---customer :%lu,%d\n",pthread_self(),pdel->data);
		free(pdel);
		pthread_mutex_unlock(&mutex);

	}

	return NULL;
}
int main(int argc ,char ** argv)
{
	pthread_t p1,p2;

	pthread_mutex_init(&mutex,NULL);  //初始化锁
	pthread_cond_init(&cond,NULL);   //初始化条件变量
	//生产者线程
	pthread_create(&p1,NULL,producer,NULL);

	//消费者线程
	pthread_create(&p2,NULL,customer,NULL);



	//阻塞回收子线程
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);

	//释放锁的资源
	pthread_mutex_destroy(&mutex);

	//释放回收条件变量的资源
	pthread_cond_destroy(&cond);

	return 0;
}
