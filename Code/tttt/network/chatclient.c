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
#include<pthread.h>
#include<stdlib.h>


#define BUFFSIZE 1024
#define MAXSIZE 1024
#define IPADDRESS "192.168.3.206"
#define SERV_PORT 4507
#define FDSIZE 1024
#define SIZE 30
typedef struct node
{
	char name[SIZE];
	char number[SIZE];
	char password[SIZE];
	char phonenumber[SIZE];
	char friendname[SIZE];
	int flag;

}loginnode;

char chat[1024];
//void my_err(const char * err_string,int line);

int login_connect(int conn_fd);
int Account_login(conn_fd);
int *main_recv(void *arg);
//int conn_fd;
int main(int argc,char **argv)
{
	int i;
	pid_t tid;
	int ret,ret2;
	int conn_fd;
	int serv_port;
	struct sockaddr_in serv_addr;
	char recv_buf1[BUFFSIZE];

	conn_fd = socket(AF_INET,SOCK_STREAM,0);
	printf( "mainrecv = %d\n",conn_fd);
	
	memset(&serv_addr,0,sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET,IPADDRESS,&serv_addr.sin_addr);
	if(connect(conn_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) < 0)   my_err("connect",__LINE__);

	
	if(pthread_create(&tid,NULL,(void *)main_recv,(void *)conn_fd) != 0)
	{
		perror("recv pthread\n");
		exit(1);
	}

	while(1)
	{
		int re;
		login_connect(conn_fd);
		gets(chat);
		getchar();
		getchar();
	//	if((ret = (send(conn_fd,chat,strlen(chat) + 1,0))) < 0)
	//	{
	//		printf( "错误 \n");
	//	}

	//	printf( "ret1 = %d\n ",ret);
//		if(( re = send(conn_fd,chat,strlen(chat),0)) < 0)  my_err("client send err",__LINE__);
	//	login_connect(conn_fd);
		if(strcmp(chat,"exit") == 0)  break;
		memset(chat,0,sizeof(chat));
	}

	close(conn_fd);

	return 0;

}
int login_connect(int conn_fd)
{
	int command;

	printf( "欢迎使用chat\n");
	printf( "请输入你的选项\n");
	printf( "[1]  登录\n");
	printf( "[2]  注册\n");
	printf( "[3]  修改密码\n");
	printf( "[4]  找回密码\n");
	printf( "[5]  退出\n");

	scanf( "%d",&command);
	getchar();

	switch(command)
	{
		case 1:
			Account_login(conn_fd)	; break;
		case 2:
	//		regist();break;
		case 3:
	//		updatapassword();break;
		case 4:
	//		foudpassword();break;
		case 5:
	//		exit(1);break;
		default :
			printf( "选项错误\n");

	}
}

int Account_login(int conn_fd)
{
	int re = 0;
	loginnode log;

	char temp[SIZE];

	//	while(1)
	{
		char buf[BUFFSIZE];
		printf("请输入昵称:");
		gets(log.name);
		printf( "请输入账号:");
		gets(log.number);
		printf( "请输入密码:");
		gets(log.password);
		while(1)
		{
			printf("请重新输入密码 :");
			gets(temp);
			if(strcmp(temp,log.password) == 0)  break;
		}
		printf( "密保问题: 手机号 :");
		gets(log.phonenumber);
		printf( "密保问题: 友好朋友的名字 :");
		gets(log.friendname);
		log.flag = 1;
		memset(buf,0,1024);    //初始化
		memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
		if((re = (send(conn_fd,buf,sizeof(loginnode) + 1,0))) < 0)  printf( "错误\n");	
	}

	printf( "发送\n");
	
	return 0;
}

int *main_recv(void *arg)
{
	char recv_buf[BUFFSIZE];
	int  conn_fd = (int)arg;

	printf( "recv main = %d\n",conn_fd);
	int ret;
	while(1)
	{
	//	while(1)
		{
			if((ret = recv(conn_fd,recv_buf,1024,0)) < 0)  my_err("recv",__LINE__);
	//		if(ret > 50 ) break;
		}
		printf( "main_ret = %d\n",ret);
		printf( "%s",recv_buf);
		printf( "\n");
	}
}
