#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define normal 0 //一般命令
#define out_redirect 1 //输出重定向
#define in_redirect 2  //输入重定向
#define have_pipe   3  //命令中有管道


int main()
{
    int i;
    int  argcount = 0;
    char arglist[100][256];
    char **arg = NULL;
    char *buf = NULL;

    buf = (char *)malloc(256);
    return 0;
}

