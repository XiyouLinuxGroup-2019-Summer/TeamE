#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *home;
    home = getenv("HOME");
    printf("home path : %s\n",home);
    return 0;
}

