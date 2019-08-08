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
#define SERV_PORT 45070
#define FDSIZE 1024
#define SIZE 30
#define MGSZIE 512
typedef struct 
{
	int  flag;
	int  id;
	char name[SIZE];
	char account[SIZE];  //account
	char password[SIZE];
	char phonenumber[SIZE];
	char friendname[SIZE];
	char updata_or_foundpassword[SIZE];
	int  result;
}loginnode;

typedef struct
{
	int  flag;
	int  id;
	int  result;
	char account[SIZE];
	char name[SIZE];
	char sex[SIZE];
	char data[SIZE];
	char address[SIZE];
	char constellation[SIZE];
	char email[SIZE];
}informationnode;

typedef struct 
{
	int flag ;
	char message[MGSZIE];
}mgnode;

informationnode inf;  //创建一个存储用户的结构体

pthread_mutex_t mutex;  //创建一把锁
pthread_cond_t cond;    //创建一个信号


int View_information(fd);    //查看用户信息
int Modity_information(int fd);   //修改用户信息
int major_UI(int fd);    //登录有主界面
char chat[1024];
//void my_err(const char * err_string,int line);
int Flag;    //判断接收到的信息  的flag
int command_analy_flag(char a[5]);   //分析命令
int login_connect(int conn_fd);     //登录主界面
int Account_login_UI(int conn_fd);   //登录
int Account_regist_UI(int conn_fd);    //注册
int Account_updatapassword_UI(int conn_fd);  //修改密码
int Account_foundpassword_UI(int conn_fd);   //找回密码

int *main_recv(void *arg);  //新开线程,负责收消息


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
	int conre; 
	int optval;
	optval = 1;
	if(setsockopt(conn_fd,SOL_SOCKET,SO_REUSEADDR,(void *) &optval,sizeof(int)) < 0)  my_err("setsockopt",__LINE__);

	if(conre = connect(conn_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) < 0)   my_err("connect",__LINE__);

	printf( "conre = %d\n",conre);
	if(pthread_create(&tid,NULL,(void *)main_recv,(void *)pthread_conn_fd) != 0)
	{
		perror("recv pthread\n");
		exit(1);
	}

//	while(1)
	{
		int re;
		login_connect(conn_fd);
		//gets(chat);
		//getchar();
		//getchar();
	//	if((ret = (send(conn_fd,chat,strlen(chat) + 1,0))) < 0)
	//	{
	//		printf( "错误 \n");
	//	}

	//	printf( "ret1 = %d\n ",ret);
//		if(( re = send(conn_fd,chat,strlen(chat),0)) < 0)  my_err("client send err",__LINE__);
	//	login_connect(conn_fd);
//		if(strcmp(chat,"exit") == 0)  break;
//		memset(chat,0,sizeof(chat));
	}

	close(conn_fd);

	return 0;

}
int login_connect(int conn_fd)
{
	int command;
	int success = 0;    //判断是否成功进行操作  1为成功,2 为失败
	do
	{
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
				success = Account_login_UI(conn_fd);
				if(success == 0)    continue;
				major_UI(conn_fd);
				break;
			case 2:
				success = Account_regist_UI(conn_fd);break;
			case 3:
				success = Account_updatapassword_UI(conn_fd);break;
			case 4:
				success = Account_foundpassword_UI(conn_fd);break;
			case 5:
		//		exit(1);
				break;
			default :
				printf( "选项错误\n");

		}
	}while(command != 5);
}
int Account_foundpassword_UI(int conn_fd)
{

	loginnode log;
	int re = 0;
	log.flag = 4;
	char buf[BUFFSIZE];
	int result;
	printf( "****** 找回密码 *******\n");
	printf( "请输入账号:");
	gets(log.account);
	printf( "请输入预留手机号:");
	gets(log.phonenumber);
	printf( "请输入最好的朋友的名字:");
	gets(log.friendname);
	
	memset(buf,0,1024);    //初始化
	memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
	if((re = (send(conn_fd,buf,1024,0))) < 0)  printf( "错误\n");	
	
	//printf( "found re = %d\n",re);

	pthread_mutex_lock(&mutex);   //加锁  ,对全局变量进行操作
        pthread_cond_wait(&cond,&mutex);
	
	result = Flag;

        pthread_mutex_unlock(&mutex);

	
	return result;
}
int Account_updatapassword_UI(int conn_fd)
{
	int result;
	loginnode log;
	log.flag = 3;
	char buf[BUFFSIZE];
	char temppassword[SIZE];
	int re = 0;
	printf( "******** 修改密码 ***********\n");
	printf( "请输入账号:");
	gets(log.account);
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
	if((re = (send(conn_fd,buf,1024,0))) < 0)  printf( "错误\n");	

	pthread_mutex_lock(&mutex);   //加锁  ,对全局变量进行操作
        pthread_cond_wait(&cond,&mutex);
	
	result = Flag;

        pthread_mutex_unlock(&mutex);
	printf( "updata re = %d\n",re);

	return result;
}
int Account_login_UI(int conn_fd)
{
	int result;
	int re = 0;
	char buf[BUFFSIZE];
	loginnode log;
	printf("请输入账号: ");
	gets(log.account);
	printf("请输入密码: ");
	gets(log.password);
	log.flag = 1;
	memset(buf,0,1024);    //初始化
	memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
	if((re = (send(conn_fd,buf,1024,0))) < 0)  printf( "错误\n");	
	
	printf( "加锁\n");
	pthread_mutex_lock(&mutex);   //加锁  ,对全局变量进行操作
        pthread_cond_wait(&cond,&mutex);
	result = Flag;

        pthread_mutex_unlock(&mutex);
	
	strcpy(inf.account,log.account);

	printf( "login re = %d\n",re);

	return result;
}

int Account_regist_UI(int conn_fd)
{
	int re = 0;
	loginnode log;
	int result;
	char temp[SIZE];
	char buf[BUFFSIZE];
	printf("请输入昵称:");
	gets(log.name);
	printf( "请输入账号:");
	gets(log.account);
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
	log.flag = 2;
	memset(buf,0,1024);    //初始化
	memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
	if((re = (send(conn_fd,buf,1024,0))) < 0)  printf( "错误\n");	
	
	pthread_mutex_lock(&mutex);   //加锁  ,对全局变量进行操作
        pthread_cond_wait(&cond,&mutex);
	
	result = Flag;

        pthread_mutex_unlock(&mutex);
	printf( "send_re = %d\n",re);
	printf( "发送\n");
	
	return result;
}

int *main_recv(void *arg)
{
	loginnode log;
	char recv_buf[BUFFSIZE];
	int  fd = (int)arg;   //转化 fd
	char *p = recv_buf;   //用来接受信息
	int ret;  
	int ret1;
	int lack;
	int judge = 0;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);

	char anly[5];   //解析命令
	while(1)
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
		printf( "输出\n");
//		printf( "main_ret = %d\n",ret);
		strncpy(anly,recv_buf,sizeof(int));
	//	printf( "解析之前flag = %d\n",log.flag);

		judge = command_analy_flag(anly);

		//printf( "%s",recv_buf);
		//printf( "\n");
		switch(judge)
		{
			case 1:
			case 2:
			case 3:
			case 4:
				memset(&log,0,sizeof(loginnode));
        	 		memcpy(&log,recv_buf,sizeof(loginnode));    //将结构体的内容转为字符串
				break;
		}
		printf( "judge = %d\n",judge);
		pthread_mutex_lock(&mutex);
		switch(judge)
		{
			case 1:
				if(log.result == 1)
				{
					printf( "登录成功\n");
					inf.id = log.id;
					Flag = 1;
				}
				else
				{
					printf( "登录失败\n");
					Flag = 0;
				}
				break;
			case 2:
				if(log.result == 1)
				{
					printf( "注册成功\n");
					Flag = 1;
				}
				else
				{
					printf( "注册失败\n");
					printf( "账号已经被使用\n");
					Flag = 0;
				}
				break;
			case 3:
				if(log.result == 1)
				{
					Flag = 1;
					printf( "修改成功\n");
					printf( "新密码为 %s:\n",log.updata_or_foundpassword);
				}
				else
				{
					Flag = 0;
					printf( "修改失败\n");
				}break;
			case 4:
				if(log.result == 1)
				{
					printf( "找回成功\n");
					printf( "密码为:%s\n",log.updata_or_foundpassword);
					Flag = 1;
				}
				else
				{
					Flag = 0;
					printf( "找回失败\n");
				}
				break;
			case 5:
				if(inf.flag == 1)
				{
					printf( "用户信息修改成功\n");
					Flag = 1;
				}
				else
				{
					printf( "用户信息修改失败\n");
					Flag = 0;
				}
		}

                pthread_mutex_unlock(&mutex);
                pthread_cond_signal(&cond);


				
	}
	
}

int command_analy_flag(char a[5])    //用来解析flag
{
	int flag;
	memcpy(&flag,a,sizeof(int));
	return flag;
}

int major_UI(int fd)
{
	int command;
	do
	{
		printf( "[1]  好友管理\n");
		printf( "[2]  聊天通信\n");
		printf( "[3]  群管理\n");
		printf( "[4]  传送文件\n");
		printf( "[5]  修改信息\n");
		printf( "[6]  查看用户信息\n");
		printf( "[7]  退出\n");
	
		printf( "请输入选项\n");
		scanf( "%d",&command);
		getchar();
	
		switch(command)
		{
	
			case 1:
	//			Friend_management_UI();
				break;
			case 2:
	//			Chat_communication_UI();
				break;
			case 3:
	//			Group_management_UI();
				break;
			case 4:
	//			File_transfer_UI();
				break;
			case 5:
				Modity_information(fd);
				break;
			case 6:
	//			View_information(fd);
			default :
				printf( "选项错误\n");
		}		
	}while(command != 7);
}
int Modity_information(int fd)
{
 	 int re;
	 int result;
	 inf.flag = 5;
	 char buf[1024];
	 // inf 已知 用户的 主键 id,和账号
	 printf("请输入昵称:");
	 gets(inf.name);
	 printf("请输入性别:");
	 gets(inf.sex);
	 printf("请输入出生日期:");
	 gets(inf.data);
	 printf("请输入地址:");
	 gets(inf.address);
	 printf( "请输入星座:");
	 gets(inf.constellation);
	 printf( "请输入邮箱:");
	 gets(inf.email);
	 memset(buf,0,1024);    //初始化
	 memcpy(buf,&inf,sizeof(informationnode));    //将结构体的内容转为字符串
	
	 if((re = (send(fd,buf,1024,0))) < 0)  printf( "错误\n");

	 pthread_mutex_lock(&mutex);   //加锁  ,对全局变量进行操作
	 pthread_cond_wait(&cond,&mutex);
	 result = Flag;
	 
	 pthread_mutex_unlock(&mutex);


}
int View_information(int fd)
{
         int re;
         int result;
         inf.flag = 6;
         char buf[1024];
	 //已知inf 
	 
	 memset(buf,0,1024);    //初始化                                                   
         memcpy(buf,&inf,sizeof(informationnode));    //将结构体的内容转为字符串

         if((re = (send(fd,buf,1024,0))) < 0)  printf( "错误\n");

         pthread_mutex_lock(&mutex);   //加锁  ,对全局变量进行操作
         pthread_cond_wait(&cond,&mutex);
         result = Flag;
         
         pthread_mutex_unlock(&mutex);




}
