#include "condition.h"

//初始化互斥量和条件变量
//参数表示封装的状态
//0表示初始化成功，其他任何非0表示初始化失败
int condition_init(condition_t *cond)
{
    int status;
    if((status = pthread_mutex_init(&cond->pmutex,NULL)))
        return status;
    if((status = pthread_cond_init(&cond->pcond,NULL)))
        return status;
    return 0;
}

//加锁
//参数cond表示封装的状态
//成功加锁后会返回0，否则阻塞
int condition_lock(condition_t *cond)
{
    return pthread_mutex_lock(&cond->pmutex);
}

//解锁
//参数cond表示状态结构体
//成功解锁后返回0,其他异常
int condition_unlock(condition_t *cond)
{
    return pthread_mutex_unlock(&cond->pmutex);
}

//等待
//成功阻塞之后会返回0
int condition_wait(condition_t* cond)
{
    return pthread_cond_wait(&cond->pcond,&cond->pmutex);
}

//固定时间等待
//状态结构体　和　阻塞时间(秒+纳秒)
//成功阻塞返回0
int condition_timewait(condition_t *cond,const struct timespec* abstime)
{
    return pthread_cond_timedwait(&cond->pcond,&cond->pmutex,abstime);
}

//唤醒一个睡眠线程
int condition_signal(condition_t* cond)
{
    return pthread_cond_signal(&cond->pcond);
}

//唤醒所有睡眠线程
int condition_brodcast(condition_t *cond)
{
    return pthread_cond_broadcast(&cond->pcond);
}

//销毁互斥锁和条件变量
//成功销毁返回0
int condition_destory(condition_t *cond)
{
    int status;
    if((status = pthread_mutex_destroy(&cond->pmutex)))
        return status;
    if((status = pthread_cond_destroy(&cond->pcond)))
        return status;
    return 0;
}
