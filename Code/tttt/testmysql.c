#include <stdlib.h>  
#include <stdio.h>  
#include <mysql/mysql.h>  
int main() {  
    MYSQL *conn_ptr;  
  
    conn_ptr = mysql_init(NULL);  
    if (!conn_ptr) {  
        printf("mysql_init failed\n");  
        return EXIT_FAILURE;  
    }  
    conn_ptr = mysql_real_connect(conn_ptr, "localhost", "root", "073848", "test",4507, NULL, 0);  
    //root 为用户名 123456为密码 test为要连接的database  
  
    if (conn_ptr) {  
        printf("Connection success\n");  
    } else {  
        printf("Connection failed\n");  
    }

    return EXIT_SUCCESS;  
}  
