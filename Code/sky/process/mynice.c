#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/wait.h>
int main()
{
    pid_t pid;
    int stat_val = 0;
    int oldpri,newpri;
    printf("进程优先级学习!\n");

    pid = fork();
    switch(pid)
    {
        case 0:
            printf("子进程正在运行，子进程ID:%d,父进程ID:%d\n",getpid(),getppid());
            oldpri = getpriority(PRIO_PROCESS,getpid());
            printf("子进程旧的优先级是:%d\n",oldpri);

            newpri = nice(18);
            printf("子进程新的优先级是:%d\n",newpri);
            break;
        case -1:
            printf("进程fork失败!\n");
            exit(-1);
            break;
        default:
            wait(&stat_val);
            printf("父进程正在运行!\n");
            break;
    }
    return 0;
}

