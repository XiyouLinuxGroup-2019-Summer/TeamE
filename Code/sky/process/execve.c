#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
int main(int argc,char **argv,char ** environ)
{
    pid_t pid;
    int stat_val;
    printf("exec例子\n");

    pid = fork();
    switch(pid)
    {
         case -1:
            perror("进程创建失败!\n");
            exit(1);
        case 0:
            printf("子进程正在运行!\n");
            printf("子进程= %d,父进程 = %d\n",getpid(),getppid());
            printf("uid = %d,gid = %d",getuid(),getgid());
            execve("processimage",argv,environ);
            printf("进程永远不会到这儿来!\n");
            exit(0);
        default:
            wait(&stat_val);
            printf("父进程正在运行!\n");
            break;

    }
    exit(0);

    return 0;
}

