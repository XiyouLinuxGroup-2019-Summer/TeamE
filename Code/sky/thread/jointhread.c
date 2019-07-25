#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void assistthread()
{
    printf("我正在帮助去做一些工作\n");
    sleep(1);
    pthread_exit(100);
}
int main()
{
    pthread_t assistthid;
    int  status;

    pthread_create(&assistthid,NULL,(void*)assistthread,NULL);
    pthread_join(assistthid,(void*)&status);
    printf("assistthread退出码为:%d",status);
    return 0;
}

