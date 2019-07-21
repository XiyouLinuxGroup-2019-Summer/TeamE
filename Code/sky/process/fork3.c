#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
    pid_t  pid;
    pid = fork();
    switch(pid)
    {
        case 0:
            {
            int a = 10;
            while(1)
            {
                printf("子进程正在运行,子进程ID:%d,父进程ID:%d\n",getpid(),getppid());
                sleep(1);
            }
            }
            break;
        case -1:
            printf("进程创建失败!\n");
            exit(-1);
            break;
        default:
            printf("父进程正在运行,子进程:%d 该进程:%d\n",pid,getpid());
            exit(0);
            return 0;
    }
    return 0;
}

