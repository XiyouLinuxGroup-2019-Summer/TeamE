#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"my_recv.h"

#define INVALID_USERINFO 'n'  //用户信息无效
#define VALID_USERINFO 'y'     //用户信息有效

//获取用户输入到 buf ,buf 的长度为 len,用户输入数据以'\n'为结束标志
int get_userinfo(char *buf,int len)
{
	int i;
	int c;
	if(buf ==  NULL)  return -1;

	i = 0;
	while(((c = getchar()) != '\n') && (c != EOF) && (i < len-2))
	{
		buf[i++] = c;
	}

	buf[i++] = '\n';
	buf[i++] = '\0';

	return 0;
}

//输入用户名,然后用过fd 发送出去
void input_userinfo(int conn_fd,const char *string)
{
	char input_buf[32];
	char recv_buf[BUFSIZE];
	int flag_userinfo;

	//输入用户信息直到正确为止
	
	do
	{
		printf( "%s: ",string);
		if(get_userinfo(input_buf,32) < 0)
		{
			printf( "error return from get_userinfo\n");
			exit(1);
		}

		if(send(conn_fd,input_buf,strlen(input_buf),0) < 0)  my_err("send",__LINE__);

		//从连接套接字上读取上一次数据

		if(my_recv(conn_fd,recv_buf,sizeof(recv_buf)) < 0)
		{
			printf( "data is too long\n");
			exit(1);
		}

		if(recv_buf[0] == VALID_USERINFO)
		{
			flag_userinfo = VALID_USERINFO;
		}
		else
		{
			printf( "%s error,input again,",string);
			flag_userinfo = INVALID_USERINFO;
		}
	}while(flag_userinfo == INVALID_USERINFO);
}


