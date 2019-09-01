#include"apue.h"

int main()
{
	int c;
	           //getc   一次读取一个字符
	while((c = getc(stdin)) != EOF)
	{         //putc   一次输出一个字符
		if(putc(c,stdout) == EOF)  
		{
			printf( "output error");
		}
	}


	if(ferror(stdin))   printf("input error");

	exit(0);

}
