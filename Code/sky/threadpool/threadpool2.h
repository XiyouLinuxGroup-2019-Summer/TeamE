#ifndef _THREADHPOOL_H_
#include <threads.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct task
{
    void *(*process) (void*arg);//函数指针，指向任务
    void *arg;                  //回调函数的参数
    struct task *next;          //指向下一个任务
}task_t;

typedef struct thread_pool
{
    pthread_mutex_t queue_lock;
    pthread_cond_t queue_cond;

    task_t* queue_head;

    int shutdown;
    pthread_t *threadid;

    int max_thread_num;
    int cur_queue_size;
}thread_pool;

void threadpool_init(int max_thread_num);
int threadpool_destroy();
void *thread_routine();
int pool_add_task(void*(*process)(void*arg),void *arg);
#endif
