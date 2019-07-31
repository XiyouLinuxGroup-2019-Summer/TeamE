#ifndef _THREAD_POLL_H_
#define _THREAD_POLL_H_

//需要引入状态的头文件---条件变量和互斥锁
#include "condition.h"

//封装任务对象相当于链表中的一个个节点
typedef struct task
{
    void *(*run) (void *args);//函数指针，需要执行的任务
    void *args; //参数
    struct task *next; //任务队列中下一个任务
}task_t;

//线程池结构体相当于链表头指针
typedef struct threadpool
{
    condition_t ready; //状态量是一个封装的结构体
    task_t *first;       //任务队列中的第一个任务
    task_t *last;        //任务队列中的最后一个任务
    int counter;       //线程池中已有的线程数
    int idle;          //线程池中空闲的线程数
    int max_threads;   //线程池中的最大线程数
    int quit;          //是否退出标志0/1
}threadpool_t;


#endif
