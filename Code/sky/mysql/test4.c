//从表中获取数据
#include <stdio.h>
#include <my_global.h>
#include <mysql.h>


int main()
{
    MYSQL *con = mysql_init(NULL);
    if(con == NULL){
        fprintf(stderr,"%s\n",mysql_error(con));
    }

    if(mysql_real_connect(con,"localhost","user123","123456","mydb",123,NULL,0) == NULL){
        printf("error:%d\n",__LINE__);
    }

    if(mysql_query(con,"SELECT *FROM Phones")){
        printf("err:%d\n",__LINE__);
    }

    MYSQL_RES *result = mysql_store_result(con);
    if(NULL == result){
        printf("error:%d\n",__LINE__);
    }
    
    int num_fields = mysql_num_fields(result);
    MYSQL_ROW  row;

    while((row = mysql_fetch_row(result))){
        for(int i = 0;i<num_fields;i++){
            printf("%s ",row[i]?row[i]:"NULL");
        }
        printf("\n");
    }

    mysql_free_result(result);
    mysql_close(con);
    return 0;
}

