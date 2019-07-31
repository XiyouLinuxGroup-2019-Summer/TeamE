#include <stdio.h>
#include <pthread.h>
#include "threadpool2.h"
void  *func(void *arg)
{
    printf("");
    /* printf("线程[0x%lx]正在运行任务[%d]\n",pthread_self(),*(int*)arg); */
    return NULL;
}

int main()

{
    time_t begin = clock();
    threadpool_init(800);
    //向线程池中投入10个任务
    int *tasknum = (int *)malloc(sizeof(int)*100000);
    for(int i = 0;i<100000;i++)
    {
        tasknum[i] = i;
        /* printf("%d\n",i+1); */
        pool_add_task(func,&tasknum[i]);
    }
    sleep(5);
    threadpool_destroy();
    free(tasknum);
    time_t end = clock();
    printf("time = %ld\n",end-begin);
    return 0;
}

