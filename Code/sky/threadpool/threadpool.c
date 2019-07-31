#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "threadpool.h"
#include <error.h>
#include <string.h>
#include <stdlib.h>
//线程池初始化
//pool表示线程池头指针，idle_threads表示空闲线程数目，max_threads表示线程池中最大的线程数
void threadpool_init(threadpool_t *pool,int idle_threads,int max_threads)
{
    //头指针的初始化
    condition_init(&pool->ready);//初始化状态结构体
    pool->first = NULL;
    pool->last = NULL;
    pool->counter = 0;
    pool->idle = 0;
    pool->max_threads = max_threads;
    pool->quit = 0;

    //创建空闲线程
    for(int i = 0;i<idle_threads;i++)
    {
        pthread_t tid;
        pthread_create(&tid,NULL,thread_routine,pool);
        pool->counter++;
    }
}


//线程池中创建的线程执行
void *thread_routine(void *arg)//线程顺序
{
    struct timespec abstime;//时间结构体
    int timeout;
    printf("主线程[%d]开始\n",(int)pthread_self());

    threadpool_t *pool = (threadpool_t *)arg;//类似头指针
    
    //死循环可以使线程池中的线程可以复用
    while(1)
    {
        timeout = 0;

        //访问线程池之前需要加锁
        condition_lock(&pool->ready);

        //空闲线程加一
        pool->idle++;

        //任务队列没有任务到来气人没有收到线程池的销毁通知
        //线程阻塞等待进入这里面的都是空闲线程等待被唤醒
        while(pool->first == NULL && !pool->quit)
        {
            printf("线程[%d]处于空闲状态\n",(int)pthread_self());
            
            //获取当前时间，并且加上等待事件
            //从而设置超时睡眠时间
            
            clock_gettime(CLOCK_REALTIME,&abstime);//获取当前时间
            abstime.tv_sec += 2;
            
            //该函数会解锁云粗其他线程访问
            int status = condition_timewait(&pool->ready,&abstime);
            if(status == ETIMEDOUT)
            {
                printf("线程[%d]等待超时\n",(int)pthread_self());
                timeout = 1;
                break;
            }
            
        }
    }
    
    return 0;
}

