#ifndef _CONDITION_H_
#define _CONDITION_H_

//用条件变量和互斥量来保证线程池的安全

#include <pthread.h>

//封装一个互斥量(锁)和条件变量状态
typedef struct condition
{
    pthread_mutex_t pmutex;
    pthread_cond_t pcond;
}condition_t;

//对状态进行操作的函数

int condition_init(condition_t *cond);
int condition_lock(condition_t *cond);
int condition_unlock(condition_t *cond);
int condition_wait(condition_t* cond);
int condition_timewait(condition_t *cond,const struct timespec* abstime);
int condition_signal(condition_t* cond);
int condition_brodcast(condition_t *cond);
int condition_destory(condition_t *cond);
#endif
