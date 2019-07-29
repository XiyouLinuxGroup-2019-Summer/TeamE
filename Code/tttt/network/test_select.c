#include<stdio.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>


void display_time(const char *string)
{
	int seconds;
	seconds = time((time_t*)NULL);
	printf( "%s , %d\n",string,seconds);
}

int main()
{
	fd_set readfds;   //初始化 一个集合描述符
	struct timeval timeout;
	/*struct timeval
	 * {
	 *    long tv_sec;    //指定秒数
	 *    long tv_usec;   //指定微秒数
	 * }
	 */
	int ret;

	//监视文件描述符 0 是否有数据输入,文件描述符 0 表示标准输入即键盘输入
	FD_ZERO(&readfds);    //开始使用一个描述符集合前一般要将其清空
	FD_SET(0,&readfds); //在文件描述符 set 增加文件描述符 fd

	//设置阻塞时间 为 10秒
	timeout.tv_sec = 10;
	timeout.tv_usec = 10;

	while(1)
	{
		display_time("before select");
		ret = select(1,&readfds,NULL,NULL,&timeout);  //当监视的文件描述符上什么时间都没有发生,则返回 0
		display_time("after select");

		switch(ret)
		{
			case 0:printf( "No data in ten seconds.\n");
			       exit(0);
			       break;
			case -1: perror("select");
				 exit(1);
				 break;
			default: getchar() ;  //将数据读入,否则标准输入上将一直为读就绪
				 printf("data is available now.\n");
		}
	}

	return 0;
}

