#include <stdio.h>
#include <my_global.h>
#include <mysql.h>
int main()
{
    MYSQL *con = mysql_init(NULL);//初始化返回一个句柄
    if(con == NULL){
        fprintf(stderr,"%s\n",mysql_error(con));
        return -1;
    }
    
    //检查是否连接成功 connet(句柄，主机名，账号，密码，数据库名，端口号，unix套接字，客户端标记)
    if((mysql_real_connect(con,"localhost","root","2422503084.",NULL,0,NULL,0)) == NULL){
        fprintf(stderr,"%s\n",mysql_error(con));
        mysql_close(con);
        return -1;
    }

    //执行一个SQL语句创建新的数据库mygdb
    if(mysql_query(con,"CREATE DATABASE mydb")){
       fprintf(stderr,"%s\n",mysql_error(con));
       mysql_close(con);
       return -1;
    }

    printf("%s\n",mysql_get_server_info(con));
    printf("%s\n",mysql_get_host_info(con));

    mysql_close(con);

    return 0;
}

