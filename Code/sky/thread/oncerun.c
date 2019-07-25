#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_once_t once = PTHREAD_ONCE_INIT;
void run(void)
{
    printf("线程：%lu正在运行此函数\n",pthread_self());
}

void thread1()
{
    pthread_t thid = pthread_self();
    printf("当前进程是:%lu",thid);
    pthread_once(&once,run);
}
void thread2()
{
    pthread_t thid = pthread_self();
    printf("当前进程是:%lu",thid);
    pthread_once(&once,run);
}

int main()
{
    pthread_t thid1,thid2;

    pthread_create(&thid1,NULL,(void*)thread1,NULL);
    pthread_create(&thid2,NULL,(void*)thread2,NULL);

    sleep(3);
    printf("主线程退出");
    return 0;
}

