#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

FILE *open_file(char *filename)
{
    FILE *stream;
    errno = 0;

    stream = fopen(filename,"r");
    if(stream == NULL)
    {
        printf("打不开文件%d，错误原因:%s\n",__LINE__,strerror(errno));
    }
    else return stream;
}
int main()
{
    char *filename = "test";

    open_file(filename);
    return 0;
}

