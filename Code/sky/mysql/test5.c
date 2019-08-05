#include <stdio.h>
#include <my_global.h>
#include <mysql.h>

int main()
{
    MYSQL *con = mysql_init(NULL);
    if(con == NULL){
        fprintf(stderr,"%s\n",mysql_error(con));
        return -1;
    }

    if(mysql_real_connect(con,"localhost","user123","123456","mydb",0,NULL,0) == NULL){
        fprintf(stderr,"错误%d\n",__LINE__);
    }

    if(mysql_query(con,"drop table if exists writers")){
        fprintf(stderr,"错误%d\n",__LINE__);
    }

    char *sql = "CREATE TABLE Writers(ID INT PRIMARY KEY AUTO_INCREMENT,NAME TEXT)";
    
    if(mysql_query(con,sql)){
        fprintf(stderr,"错误%d\n",__LINE__);
    }
    


    return 0;
}

