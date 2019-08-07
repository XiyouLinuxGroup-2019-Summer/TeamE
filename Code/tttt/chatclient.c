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
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 4507
#define FDSIZE 1024
#define SIZE 30
typedef struct node
{
	int flag;
	char name[SIZE];
	char number[SIZE];
	char password[SIZE];
	char phonenumber[SIZE];
	char friendname[SIZE];
	char updata_or_foundpassword[SIZE];
}loginnode;

char chat[1024];
//void my_err(const char * err_string,int line);

int login_connect(int conn_fd);
int Account_login(int conn_fd);
int *main_recv(void *arg);
//int conn_fd;
int main(int argc,char **argv)
{
	int i;
	pthread_t tid;
	int ret,ret2;
	int conn_fd;
	int serv_port;
	struct sockaddr_in serv_addr;
	char recv_buf1[BUFFSIZE];

	conn_fd = socket(AF_INET,SOCK_STREAM,0);
	int pthread_conn_fd = conn_fd;
	
	memset(&serv_addr,0,sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET,IPADDRESS,&serv_addr.sin_addr);
	if(connect(conn_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) < 0)   my_err("connect",__LINE__);

	
	if(pthread_create(&tid,NULL,(void *)main_recv,(void *)pthread_conn_fd) != 0)
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
			Account_login_UI(conn_fd);break;
		case 2:
			Account_regist_UI(conn_fd);break;
		case 3:
			Account_updatapassword_UI(conn_fd);break;
		case 4:
			Account_foundpassword_UI(conn_fd);break;
		case 5:
	//		exit(1);break;
		default :
			printf( "选项错误\n");

	}
}
int Account_foundpassword_UI(int conn_fd)
{

	loginnode log;
	int re = 0;
	log.flag = 4;
	char buf[BUFFSIZE];
	
	printf( "****** 找回密码 *******\n");
	printf( "请输入账号:");
	gets(log.number);
	printf( "请输入预留手机号:");
	gets(log.phonenumber);
	printf( "请输入最好的朋友的名字:");
	gets(log.friendname);
	
	memset(buf,0,1024);    //初始化
	memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
	if((re = (send(conn_fd,buf,sizeof(loginnode) + 1,0))) < 0)  printf( "错误\n");	
	
	printf( "found re = %d\n",re);


	return 0;



}
int Account_updatapassword_UI(int conn_fd)
{
	loginnode log;
	log.flag = 3;
	char buf[BUFFSIZE];
	char temppassword[SIZE];
	int re = 0;
	printf( "******** 修改密码 ***********\n");
	printf( "请输入账号:");
	gets(log.number);
	printf( "请输入旧密码");
	gets(log.password);
	printf( "请输入新密码");
	gets(log.updata_or_foundpassword);
	while(1)
	{
		printf( "请重新输入新密码:");
		gets(temppassword);
		if(strcmp(temppassword,log.updata_or_foundpassword) == 0)	break;
	}

	memset(buf,0,1024);    //初始化
	memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
	if((re = (send(conn_fd,buf,sizeof(loginnode) + 1,0))) < 0)  printf( "错误\n");	

	printf( "updata re = %d\n",re);


}
int Account_login_UI(int conn_fd)
{
	int re = 0;
	char buf[BUFFSIZE];
	loginnode log;
	printf("请输入账号: ");
	gets(log.number);
	printf("请输入密码: ");
	gets(log.password);
	log.flag = 2;
	memset(buf,0,1024);    //初始化
	memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
	if((re = (send(conn_fd,buf,sizeof(loginnode) + 1,0))) < 0)  printf( "错误\n");	
	
	printf( "login re = %d\n",re);
}

int Account_regist_UI(int conn_fd)
{
	int re = 0;
	loginnode log;

	char temp[SIZE];
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
		printf( "密码不正确\n");
	}
	printf( "密保问题: 手机号 :");
	gets(log.phonenumber);
	printf( "密保问题: 友好朋友的名字 :");
	gets(log.friendname);
	log.flag = 1;
	memset(buf,0,1024);    //初始化
	memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
	if((re = (send(conn_fd,buf,sizeof(loginnode) + 1,0))) < 0)  printf( "错误\n");	
	
	printf( "send_re = %d\n",re);
	printf( "发送\n");
	
	return 0;
}

int *main_recv(void *arg)
{
	char recv_buf[BUFFSIZE];
	int  fd = (int)arg;
	char *p = recv_buf;
	int ret;
	int ret1;
	int lack;
	while(1)
	{
//		while(1)
		{
			if((ret = recv(fd,p,1024,0)) < 0)  my_err("recv",__LINE__);
			while(1)
			{
				if(ret != 1024)
				{
					lack = 1024 - ret;
					for(int i = 0;i < ret;i++)  recv_buf[i] = *p++;
	
					if((ret1 = recv(fd,p,1024,0)) < 0)  my_err("recv",__LINE__);
					ret += ret1;
	
				}
				else break;
			}
		}
		printf( "main_ret = %d\n",ret);
		printf( "%s",recv_buf);
		printf( "\n");
		
	}
	
}
