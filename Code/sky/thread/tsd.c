#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
pthread_key_t key;

void *thread2()
{
    int tsd = 5;
    printf("thread %d 正在运行\n",pthread_self());
    pthread_setspecific(key,(void*)tsd);
    printf("thread %d 私有数据%d\n",pthread_self(),pthread_getspecific(key));
}
void *thread1()
{
    int tsd = 0;
    pthread_t  thid2;

    printf("thread%d正在运行\n",pthread_self());
    pthread_setspecific(key,(void*)tsd);
    pthread_create(&thid2,NULL,(void*)thread2,NULL);
    sleep(2);
    printf("thread%d私有数据%d\n",pthread_self(),pthread_getspecific(key));
}
int main()
{
    pthread_t thid;
    printf("主线程开始运行\n");
    pthread_key_create(&key,NULL);
    pthread_create(&thid,NULL,(void*)thread1,NULL);
    sleep(3);
    pthread_key_delete(key);
    printf("主线程退出\n");
    return 0;
}

