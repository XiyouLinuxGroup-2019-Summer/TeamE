#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
int main()
{
    FILE *stream;

    char *filename = "test";
    
    errno = 0;

    stream = fopen(filename,"r");
    if(stream == NULL)
    {
        printf("文件打开失败，错误码%d",errno);
    }
    else printf("成功打开文件\n");
    return 0;
}

