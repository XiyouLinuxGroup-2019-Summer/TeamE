#include <stdio.h>
#include <unistd.h>

int main(int argc,char **argv)
{
    char buf[64];
    chdir(argv[1]);
    getcwd(buf,sizeof(buf));
    printf("%s\n",buf);
    return 0;
}

