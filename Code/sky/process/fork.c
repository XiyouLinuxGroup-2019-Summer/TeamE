#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
//fork有两个返回值，一次是父进程的返回值，返回值是创建的子进程的ID
//另一次是子进程的返回值，创建成功返回0，失败返回-1
//一般来说fork之后，父进程先执行还是子进程限先执行是不确定的i,取决于内核的调度算法
int main()
{
    pid_t pid;

    printf("进程创建学习!\n");
    pid = fork();
    switch(pid)
    {
        case 0:
            printf("子进程正在运行，子进程ID是:%d,父进程ID是:%d\n",pid,getpid());break;
        case -1:
            printf("进程创建失败!\n");break;
        default:
            printf("父进程进程正在运行，子进程ID是:%d,父进程ID是:%d\n",pid,getpid());break;
    }
    return 0;
}

