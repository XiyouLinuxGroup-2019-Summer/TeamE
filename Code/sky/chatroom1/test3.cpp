#include <stdio.h>
#include <pthread.h>
#include <queue>
#include <unistd.h>
#include <stdlib.h>
using namespace std;
pthread_mutex_t lock;
pthread_t producer,consumer;
pthread_cond_t cond1;
pthread_cond_t cond2;
queue<int > q;
//存放生产的数据 定义：队列中元素个数为１时为满　0时为空

void *pro(void *arg)
{
    while(1){
    pthread_mutex_lock(&lock);
    if(q.size() == 1) pthread_cond_wait(&cond2,&lock);
    if(q.size() == 1){
        printf("生产者生产异常........\n");
        exit(0);
    }
    else printf("生产者正常生产\n"); 
    /* sleep(1); */
    //生产
    q.push(1);


    pthread_cond_signal(&cond1);
    pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *con(void *arg)
{
    while(1){
    pthread_mutex_lock(&lock);
    
    while(q.empty()) pthread_cond_wait(&cond1,&lock);
    if(q.empty()){
        printf("消费者消费异常.............\n");
        exit(0);
    }
    else printf("消费者正常消费\n"); 
    /* sleep(1); */
    //消费
    q.pop();

    pthread_cond_signal(&cond2);
    pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_cond_init(&cond1,NULL);
    pthread_cond_init(&cond2,NULL);
    pthread_mutex_init(&lock,NULL);
    pthread_create(&consumer,NULL, con, NULL);
    pthread_create(&producer,NULL, pro, NULL);
   // pthread_mutex_destroy(&lock);
    pthread_join(producer,NULL);
    pthread_join(consumer,NULL);
    return 0;
}

