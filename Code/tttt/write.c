#include"apue.h"

#define BUFFSIZE 4096

int main(void)
{
	int n;
	char buf[BUFFSIZE]; //标准输入  键盘                              //标准输出  文件,支持重定向
	while((n = read(STDIN_FILENO,buf,BUFFSIZE)) > 0)	if( write(STDOUT_FILENO,buf,n) != n);//  err_sys("write error");
	
	if(n < 0);   err_sys("read error");

	exit(0);
}
