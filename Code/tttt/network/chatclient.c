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
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>


#define MSGSIZE 512
#define BUFFSIZE 1024
#define MAXSIZE 1024
#define IPADDRESS "127.0.0.1"
#define SERV_PORT 45070
#define FDSIZE 1024
#define SIZE 30
#define MGSZIE 512

typedef struct
{
	int flag;
	int id;
}downonline;

typedef struct 
{
	int  flag;
	int  id;
	char online[SIZE];
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
	int  id;    //id 为 login 的id
	int  result;
	char account[SIZE];
	char name[SIZE];
	char sex[SIZE];
	char data[SIZE];
	char address[SIZE];
	char constellation[SIZE];
	char email[SIZE];
	int  line;
}informationnode;

typedef struct    //添加好友
{
	int  flag;
	int  result;
	char sendaccount[SIZE];   //
	char acceptaccount[SIZE];
	int  sendid;    //存放发送方用户id
	int  acceptid;   //存放接收方 id
	int  sendfd;     //存放发送方的套接字
	int  acceptfd;   //存放接收方的套接字

}friendnode;


typedef struct     //聊天结构体
{ 
	int flag;
	char sendaccount[SIZE];   //存放发送方的账号
	char acceptcount[SIZE];    //存放接受方的账号
	int sendid;    //存放发送方用户id
	int acceptid;   //存放接收方 id
	char msg[MSGSIZE];     //消息的最大长度
}msgnode;

typedef struct 
{
	int flag ;
	char message[MGSZIE];
}mgnode;

informationnode inf;  //创建一个存储用户信息的结构体  一旦登录 就 保存了 本用户的 id 和账号

pthread_mutex_t mutex;  //创建一把锁
pthread_cond_t cond;    //创建一个信号

int Friend_view_UI(int conn_fd);
int Friend_del_UI(int conn_fd);
int Friend_all_view(int conn_fd);
int Friend_add_send_UI(int fd);
int offonline(int fd);   //下线通知
int Friend_management_UI(int fd);   //好友管理主界面
int View_information_UI(int fd);    //查看用户信息
int Modity_information_UI(int fd);   //修改用户信息
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

void Find_freind(int fd);   //套接字 描述符
int *main_recv(void *arg);  //新开线程,负责收消息

int write_file(friendnode fid);

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
		printf( "[1]  登录\n");
		printf( "[2]  注册\n");
		printf( "[3]  修改密码\n");
		printf( "[4]  找回密码\n");
		printf( "[5]  退出\n");

		printf( "请输入你的选项 :");
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
				offonline(conn_fd);
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
	friendnode fid;
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
			case 5:
			case 6:
			case 9:   //查看好友信息
			case 10:
				//memset(&log,0,sizeof(loginnode));
        	 		memcpy(&inf,recv_buf,sizeof(informationnode));    //将结构体的内容转为字符串
				break;
			case 7:
			case 8:
				memcpy(&fid,recv_buf,sizeof(friendnode));
				break;
		}
		printf( "judge = %d\n",judge);
		printf( "result = %d\n",log.result);
		pthread_mutex_lock(&mutex);
		switch(judge)
		{
			case 1:
				if(log.result == 1)
				{
					printf( "登录成功\n");
					printf( "log.id = %d\n",log.id);
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
				if(inf.result == 1)
				{
					printf( "用户信息修改成功\n");
					Flag = 1;
				}
				else
				{
					printf( "用户信息修改失败\n");
					Flag = 0;
				}
				break;
			case 6:
				if(inf.result == 1)
				{
					printf( "账号:%s\n",inf.account);
					printf( "昵称:%s\n",inf.name);
					printf( "性别:%s\n",inf.sex);
					printf( "生日:%s\n",inf.data);
					printf( "地址:%s\n",inf.address);
					printf( "星座:%s\n",inf.constellation);
					printf( "邮箱:%s\n",inf.email);
				}
				break;
			case 7:
		//		printf("好友申请通知\n");
				write_file(fid);
				//friend_add_accept_UI(fid,fd);
				break;
			case 8:
		//		friend_add_accept_UI(fid,fd);
				break;
			case 9:
				printf("%s     %s     ",inf.account,inf.name);
				if(inf.line)   printf( "是\n");
				else           printf( "否\n");
				break;
			case 10:
				printf("%s     %s     \n",inf.account,inf.name);
				break;
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

int major_UI(int conn_fd)
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
		printf( "[7]  查看消息通知\n");
		printf( "[8]  退出\n");
	
		printf( "请输入选项 :");
		scanf( "%d",&command);
		getchar();
	
		switch(command)
		{
	
			case 1:
				Friend_management_UI(conn_fd);
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
				Modity_information_UI(conn_fd);
				break;
			case 6:
				View_information_UI(conn_fd);
				break;
			case 7:
				Find_freind(conn_fd);
				break;
			default :
				printf( "选项错误\n");
		}	
		printf( "command = %d\n",command);
	}while(command != 8);
}
int Modity_information_UI(int fd)
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
int View_information_UI(int fd)
{
         int re;
         int result;
         inf.flag = 6;
         char buf[1024];
	 //已知inf用户的主键 ID,和账号;

	 
	 memset(buf,0,1024);    //初始化                                                   
         memcpy(buf,&inf,sizeof(informationnode));    //将结构体的内容转为字符串
         
	 if((re = (send(fd,buf,1024,0))) < 0)  printf( "错误\n");
	
         pthread_mutex_lock(&mutex);   //加锁  ,对全局变量进行操作
         pthread_cond_wait(&cond,&mutex);
         result = Flag;
         
         pthread_mutex_unlock(&mutex);
	
	 getchar();
}
int Friend_management_UI(int conn_fd)
{
	int command;
	do
	{
		printf( "[1]  添加好友\n");
		printf( "[2]  删除好友\n");
		printf( "[3]  查看所有好友\n");
		printf( "[4]  查看所有在线好友\n");
		printf( "[5]  退出\n");
		printf( "请输入选项:");

		scanf( "%d",&command);
		getchar();

		switch(command)
		{
			case 1:
				Friend_add_send_UI(conn_fd);
				break;
			case 2:
				Friend_del_UI(conn_fd);
				break;
			case 3:
				Friend_all_view(conn_fd);   //查看所有好友
				usleep(1000);
				break;
			case 4:
				Friend_view_UI(conn_fd);  //查看所有在线好友
				usleep(1000);
				break;
			default :
				printf( "选项错误\n");
		}
	}while(command != 5);

	return 0;

}

int Friend_add_send_UI(int conn_fd)
{
	int re;
	char buf[1024];

	friendnode fid;
	fid.flag = 7;
	printf( "请输入你想要加为好友的 账号:");
	gets(fid.acceptaccount);
	strcpy(fid.sendaccount,inf.account);
	fid.sendid = inf.id;   //发送方的id
	fid.sendfd = conn_fd;       //发送方的套接字
	memset(buf,0,1024);    //初始化                                                   
        memcpy(buf,&fid,sizeof(friendnode));    //将结构体的内容转为字符串
        if((re = (send(conn_fd,buf,1024,0))) < 0)  printf( "错误\n");

}




int offonline(int fd)
{
	int re;
	char buf[1024];
	downonline online;
	online.id = inf.id;
	online.flag = -1;
	memset(buf,0,1024);    //初始化                                                   
        memcpy(buf,&online,sizeof(downonline));    //将结构体的内容转为字符串
        if((re = (send(fd,buf,1024,0))) < 0)  printf( "错误\n");
	printf( "re = %d\n",re);
	printf( "退出\n");
}


/*int friend_add_accept_UI(friendnode fid,int fd)
{
	char buf[1024];
	int re;
	//while(getchar() != '\n');
	printf( "账号为:%s请求加为好友!\n",fid.sendaccount);
	printf("是否同意 ? \n");
	printf( " 1 同意   0 不同意\n");
	scanf( "%d",&fid.result);
	printf( "friend_add_result = %d\n",fid.result);
	

	memset(buf,0,1024);    //初始化        
	fid.flag = 8;
        memcpy(buf,&fid,sizeof(friendnode));    //将结构体的内容转为字符串
        if((re = (send(fd,buf,1024,0))) < 0)  printf( "错误\n");
	
}
*/
int write_file(friendnode fid)
{
	int fd;
	        //操作文件不正确 会 输出乱码
	if(!(fd = open("friend.txt",O_CREAT | O_WRONLY,0777)))
	{
		printf( "文件打开失败\n");
	}
	
	//写数据
/*	int num = write(fd,&fid,sizeof(friendnode));
	fprintf(stderr,"line%d \n",__LINE__);
	perror("write");
	printf( "num = %d\n",num);*/
	if(write(fd,&fid,sizeof(friendnode)) != sizeof(friendnode))
	{
		printf( "写入失败\n");
	}

	close(fd);


}

void Find_freind(int serverfd)
{
	int num = 0;
	char ch;
	int re;
	char buf[1024];
	friendnode fid;
	int fd;
	if((fd = open("friend.txt",O_CREAT | O_APPEND,S_IRUSR | S_IWUSR)) == -1)
	{
		printf( "文件打开失败\n");
	}

	int sum = read(fd,&fid,sizeof(friendnode));
//	if(sum == 0)  printf( "没有通知\n");
//	else
	
	while(sum != 0)
	{
		printf( "是否还想继续阅读 好友请求\n");
		printf("Y / N:");
		scanf( "%c",&ch);
		getchar();
		if(ch == 'N') break;

		char ch;
		printf( "账号 为 %s 接受 %s 的好友请求\n",fid.acceptaccount,fid.sendaccount);
		printf( "是否接受?\n");
		printf( "接受 Y /拒绝 N\n");
		scanf("%c",&ch);
		getchar();
		if(ch == 'Y')   fid.result = 1;
		else  fid.result = 0;
		fid.flag = 8;
		memset(buf,0,1024);    //初始化                                                   
	        memcpy(buf,&fid,sizeof(friendnode));    //将结构体的内容转为字符串
	        if((re = (send(serverfd,buf,1024,0))) < 0)  printf( "错误\n");
		num++;     //记录已读 的几条消息  一会删除的 前 num 条消息
		//	fid.result = 1;   //将本地的 reslut 改为1 代表已经 读 过这条消息,

		sum = read(fd,&fid,sizeof(friendnode));
	}

	if(sum == 0)   printf( "无通知\n");
	close(fd);
	
	//删除 已读 数据
	if(rename("friend.txt","friend.txt_temp") < 0)   printf( "776 错误\n");

	FILE *fpsour,*fptarg;

	fpsour = fopen("friend.txt_temp","rb");
	if(NULL == fpsour)   printf( "不能打开文件 781\n");

	fptarg = fopen("friend.txt","wb");
	if(NULL == fptarg)    printf( "不能打开文件  784\n");
	
	friendnode temp;

	while(!feof(fpsour))
	{
		if(fread(&temp,sizeof(friendnode),1,fpsour))
		{
			if(num)  
			{
				num--;
				continue;
			}
			else
			{
				fwrite(&temp,sizeof(friendnode),1,fptarg);
			}
		}
	}

	fclose(fptarg);
	fclose(fpsour);
	
	remove("friend.txt_temp");
	printf( "judgeee = %d\n",fid.flag);
	printf( "restt = %d\n",fid.result);
		
}
int Friend_del_UI(int conn_fd)
{
	int re;
	char buf[1024];

	friendnode fid;
	printf( "请输入要删除好友的 账号:");
	gets(fid.acceptaccount);

	strcpy(fid.sendaccount,inf.account);   // 将本用户的 账号保存
	fid.sendid = inf.id;

	fid.flag = 9;
	memset(buf,0,1024);    //初始化 
	memcpy(buf,&fid,sizeof(friendnode));    //将结构体的内容转为字符串
       
	if((re = (send(conn_fd,buf,1024,0))) < 0)  printf( "错误\n");

	return 0;
}

int Friend_all_view( int conn_fd)
{
	int re;
	char buf[1024];

	printf( "******** 好友列表 *********\n");
	printf( "账号      昵称        是否在线\n");
	//fid.flag = 10;
	inf.flag = 10;
	memset(buf,0,1024);    //初始化 
	memcpy(buf,&inf,sizeof(informationnode));    //将结构体的内容转为字符串

	if((re = (send(conn_fd,buf,1024,0))) < 0)  printf( "错误\n");


}


int Friend_view_UI(int conn_fd)
{
	int re;
	char buf[1024];

	printf( "******** 好友列表 *********\n");
	printf( "账号      昵称     \n");

	inf.flag = 11;
	memset(buf,0,1024);    //初始化 
	memcpy(buf,&inf,sizeof(informationnode));    //将结构体的内容转为字符串

	if((re = (send(conn_fd,buf,1024,0))) < 0)  printf( "错误\n");
	
}
