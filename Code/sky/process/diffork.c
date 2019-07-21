#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
int globalvar = 5;
int main()
{
    pid_t pid;
    int var = 1,i;
    printf("fork和vfork的不同之处:\n");

    /* pid = fork(); */
    pid = vfork();
    switch(pid)
    {
        case 0:
            i = 3;
            while(i-- > 0)
            {
                printf("子进程正在运行\n");
                globalvar++;
                var++;
                sleep(1);
            }
            printf("子进程中globalvar = %d var = %d\n",globalvar,var);
            break;
        case -1:
            printf("进程创建失败!\n");
            break;
        default:
            i = 5;
            while(i-- > 0)
            {
                printf("父进程正在运行\n");
                globalvar++;
                var++;
                sleep(1);
            }
            printf("父进程中globalvar = %d var = %d\n",globalvar,var);
            break;
     }
    return 0;
}

