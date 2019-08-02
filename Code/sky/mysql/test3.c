#include <my_global.h>
#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
int finish_with_error(MYSQL *con)
{
    fprintf(stderr,"%s\n",mysql_error(con));
    mysql_close(con);
    return -1;
}
int main()
{
    MYSQL *con = mysql_init(NULL);
    if(con == NULL){
        fprintf(stderr,"%s\n",mysql_error(con));
        return -1;
    }
    else printf("数据库初始化成功\n");

    if(mysql_real_connect(con,"localhost","user123","123456","mydb",0,NULL,0) == NULL){
        finish_with_error(con);
    }
    else printf("连接数据库成功\n");

    /* if(mysql_query(con,"DROP TABLE IF EXISTS Phones")){ */
    /*     finish_with_error(con); */
    /* } */

    //建表
    /* if(mysql_query(con,"CREATE TABLE Phones (id int,name text,price int)")) */
    /* { */
    /*     finish_with_error(con); */
    /* } */
    /* else printf("建表成功\n"); */

    //插入数据
    if(mysql_query(con,"INSERT INTO Phones VALUES(1,'Samsung GALAXY',5199)")){
        finish_with_error(con);
    }
    
    if(mysql_query(con,"INSERT INTO Phones VALUES(1,'Samsung GALAXY',5199)")){
        finish_with_error(con);
    }
    if(mysql_query(con,"INSERT INTO Phones VALUES(1,'Samsung GALAXY',5199)")){
        finish_with_error(con);
    }

    mysql_close(con);
    return 0;

}
