#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int main( )
{
	FILE *stream;
	
	char *filename = "test";
	errno = 0;    //初始化为  0 
	stream = fopen(filename,"r");

	if(stream == NULL)  printf( "open file %s failed, errno is %d\n",filename,errno);   //打开文件失败就打印相应的错误值
	else  printf( "open file %s successfully\n",filename);


}
