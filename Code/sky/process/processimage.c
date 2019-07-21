#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc,char **argv,char **environ)
{
    int i;

    printf("我是一个进程映象!\n");
    printf("我的进程ID:%d,父进程ID%d",getpid(),getppid());
    printf("uid = %d,gid = %d\n",getuid(),getgid());

    for(i = 0;i<argc;i++)
        printf("argv[%d]:%s",i,argv[i]);
    return 0;
}

