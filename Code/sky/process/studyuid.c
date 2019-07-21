#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
extern int errno;
int main()
{
    int fd;

    printf("uid study:\n");
    printf("进程的uid是%d,euid是%d\n",getuid(),geteuid());

    if((fd = open("test.c",O_RDWR) == -1))
    {
        printf("文件打开失败，错误编码%d :%s\n",errno,strerror(errno));
    }
    else
    {
        printf("成功打开文件!\n");
    }

    close(fd);
    exit(0);
    return 0;
}

