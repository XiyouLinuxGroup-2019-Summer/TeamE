#include<my_global.h>
#include<mysql.h>   //全局函数声明以及标准输入输出的头文件

int main(int argc,char ** argv)
{
	printf( "MySQL client version :%s\n",mysql_get_client_info());

	return 0;
}
