#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int *thread(void *arg)//函数名代表函数的首地址
{
    pthread_t newthid;

    newthid = pthread_self();
    printf("新线程的ID是%u\n",newthid);
    return NULL;
}
int main()
{
    pthread_t thid;

    printf("主线程ID: %u\n",pthread_self()); //打印主线程的ID
    if(pthread_create(&thid,NULL,(void*)thread,NULL) != 0)
    {
        printf("线程创建失败\n");
        /* exit(1); */
    }
    printf("123\n");
    int cnt = 10;
    while(cnt--)
    {
        sleep(1);
        printf("456\n");
    }
    exit(0);
    return 0;
}

