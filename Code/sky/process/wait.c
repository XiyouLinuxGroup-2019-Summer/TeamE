#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
int main()
{
    pid_t pid;
    char *msg;
    int k;
    int exit_code;

    printf("学习怎样退出代码!\n");

    pid = fork();
    switch(pid)
    {
        case 0:
            msg = "子进程正在运行";
            k = 5;
            exit_code = 37;
            break;
        case -1:
            perror("进程创建失败!\n");
            break;
        default:
            exit_code = 0;
            break;
    }

    //如下代码无论父子进程都会执行
    //子进程pid 为 0，父进程的 pid 为子进程id
    
    if(pid != 0)//父进程等待子进程结束
    {//父进程进入这个里面
        int stat_val;
        pid_t child_pid;

        child_pid = wait(&stat_val);
        printf("\n父进程ID:%d",getpid());
        printf("子进程已经退出,子进程id是:%d",child_pid);
        if(WIFEXITED(stat_val)) printf("子进程退出代码:%d\n",WIFEXITED(stat_val));
        else printf("子进程正常退出!\n");
    }
    else
    {
        while(k-- > 0)
        {
            puts(msg);
            sleep(1); //子进程暂停5秒，父进程此时挂起
        }
    }
    exit(exit_code);
    return 0;
}
