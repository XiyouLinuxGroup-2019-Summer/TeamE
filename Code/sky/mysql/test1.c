#include <my_global.h>
#include <stdio.h>
#include <mysql.h>
int main()
{
    printf("mysql :%s\n",mysql_get_client_info());
    return 0;
}

