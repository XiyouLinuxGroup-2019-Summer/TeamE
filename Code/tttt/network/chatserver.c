#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include"list.h"
#include<errno.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<mysql/mysql.h>

#define PORT 45070
#define LISTENQ 20
#define EPOLLLEN 2000
#define BUFSIZE  1024
#define SIZE 30
#define MGSIZE 512
typedef struct node
{
        int  flag;
	int  id;
        char name[SIZE];
        char account[SIZE];
        char password[SIZE];
        char phonenumber[SIZE];
        char friendname[SIZE];
	char updata_or_foundpassword[SIZE];
	int result;
}loginnode;   //登录结构体
typedef struct
{
        int  flag;
        int  id;
        char account[SIZE];
        char name[SIZE];
        char sex[SIZE];
        char data[SIZE];
        char address[SIZE];
        char constellation[SIZE];
        char email[SIZE];
}informationnode;  //完善用户信息 结构体

typedef struct 
{
        int flag ;
        char message[MGSIZE];
}mgnode;

MYSQL mysql;
MYSQL_RES *result;

int Modity_information(informationnode inf,int fd);
int command_analy_flag(char a[5]);    //用来解析flag
int Account_updatapassword_persistence(loginnode login,int fd);
int Account_login_persistence(loginnode login,int fd);    //登录
int Account_resgine_persistence(loginnode log,int fd);  //注册
int Account_foundpassword_persistence(loginnode log ,int fd);   //找回密码

int judge_account(loginnode log,int fd);     //判断账户是否存在
//void printResult(MYSQL *mysqlPrint);  //输出数据库例的数据
static void do_write(int epfd,int fd,char *buf);    
static void do_read(int epfd,int fd,char *buf);
int listenfd_accept(int epfd,int fd);   //连接 客户端
static void handle_events(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf); // 处理事件
void my_err(const char * err_string,int line);     //错误提示
void send_data(int conn_fd,const char *string);   //发送数据

int main( )
{
	int listenfd;
	struct sockaddr_in servaddr;

	//创建一个套接字
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd < 0) my_err("socket",__LINE__);
	//设置该套接字使之可以重新绑定端口
	int optval = 1;
	if(setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(void *) &optval,sizeof(int)) < 0)  my_err("setsockopt",__LINE__);
	
	//初始化服务器端地址结构
	memset(&servaddr,0,sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//将套接字绑定到本地端口
	if(bind(listenfd,(struct sockaddr *)&servaddr,sizeof(struct sockaddr_in)) < 0)   my_err("bind",__LINE__);

	//将套接字转化为 监听套接字
	if(listen(listenfd,LISTENQ) < 0)  my_err("listen",__LINE__);

	//创建一个epoll 手柄
	int epfd;
	epfd = epoll_create(EPOLLLEN);
	struct epoll_event events[EPOLLLEN];
	struct epoll_event ev;
	ev.events = EPOLLIN;   //监听事件
	ev.data.fd = listenfd;  //被监听的套接字
	epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);
	char buf[BUFSIZE];

	//MYSQL mysql;
        //MYSQL_RES *result;
        mysql_init(&mysql);    
        if(!mysql_real_connect(&mysql,"127.0.0.1","root","073848","chat",0,NULL,0))  my_err("conect mysql",__LINE__);
     
	if(mysql_query(&mysql,"set names utf8"))  printf( "FAlse \n");

	int ret = 0;
	while(1)
	{
		//委托内核监测事件
		ret = epoll_wait(epfd,events,EPOLLLEN,-1);
		printf( "ret = %d\n",ret);
		if(ret > 0) handle_events(epfd,events,ret,listenfd,buf);

	}
		
	close(epfd);    //一定要记着关闭
}
static void handle_events(int epfd,struct epoll_event *events,int num,int listenfd,char *buf)
{
	int i,fd;
	for(int i = 0;i < num;i++)
	{
		int fd = events[i].data.fd;

		if((fd == listenfd) && (events[i].events & EPOLLIN))   listenfd_accept(epfd,fd);
		else if(events[i].events & EPOLLIN)    do_read(epfd,fd,buf);
		else if(events[i].events & EPOLLOUT)   do_write(epfd,fd,buf);
	}

}

int listenfd_accept(int epfd,int fd)
{
	int clifd;
	struct sockaddr_in cliaddr; //用来保存发起连接请求的 主机的地址和端口
	socklen_t cliaddrlen;
	struct epoll_event ev;
	
	cliaddrlen = sizeof(struct sockaddr);   //要初始化

	clifd = accept(fd,(struct sockaddr *)&cliaddr,&cliaddrlen);
	if(clifd < 0) my_err("accept",__LINE__);

	printf( "accept a new client : %s : %d \n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
	
//	send_data(clifd,"welcome login my tcp server1\n");
	
	ev.data.fd = clifd;
	ev.events = EPOLLIN;
	//向 fd 进行 add 操作 
	epoll_ctl(epfd,EPOLL_CTL_ADD,clifd,&ev);
	
	return 0;
}

static void do_read(int epfd,int fd,char *buf)
{
	char anly[5];
	loginnode log;
	int lack;    //计算还剩 多少数据 需要接收
	char *p = buf;
	int ret;
	int ret1;  // 计算 第二次 接受到的数据
	int i;           //sizeof(buf)   出错   因为 buf 是个指针,指针一次只有 8 个字节
	int judge;
	informationnode inf;
	memset(buf,0,1024);
	memset(&log,0,sizeof(loginnode));

	if((ret = recv(fd,p,1024,0)) < 0)
	{
		my_err("recv",__LINE__);
		close(fd);
	} 
	while(1)
	{   
		if(ret != 1024)
		{   
			lack = 1024 - ret;
			for(int i = 0;i < ret;i++)  buf[i] = *p++;
			if((ret1 = recv(fd,p,1024,0)) < 0)  my_err("recv",__LINE__);
			ret += ret1;
		}   
		else break;
	}   
	printf( "ret = %d\n",ret);
	if(ret == 0)
	{
		printf("client exit\n");
		epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
	
	}
	buf[ret] = '\0';  //将数据 结束标志 '\n' 替换成 字符串结束标志
//	puts(buf);
	printf( "接受\n");

	strncpy(anly,buf,sizeof(int));
	judge = command_analy_flag(anly);
	switch(judge)
	{
		case 1:
		case 2:
		case 3:
		case 4:
			memcpy(&log,buf,sizeof(loginnode));
			break;
		case 5:
			memcpy(&inf,buf,sizeof(informationnode));
			break;

	}

	printf( "flag = %d\n",log.flag);

	switch(judge)
	{
		case 1: Account_login_persistence(log,fd);break;
		case 2: Account_resgine_persistence(log,fd);break;
		case 3: Account_updatapassword_persistence(log,fd);break;
		case 4: Account_foundpassword_persistence(log,fd);break;
		case 5: Modity_information(inf,fd);break;
	}

	memset(buf,0,sizeof(buf));
}

int Account_resgine_persistence(loginnode log,int fd)
{
	int re;
	char buf[1024];

	int flag = 1;
	char send_buf[1024];
	printf( "注册\n");
	char data[1000];
	sprintf(data,"insert into login values('%d','%s','%s','%s','%s','%s')",NULL,log.account,log.password,log.name,log.phonenumber,log.friendname);
	
	if(mysql_query(&mysql,data))
	{
		printf( "false\n");
		flag = 0;
	}
	log.result = flag;
        memset(buf,0,1024);    //初始化
        memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
        if((re = (send(fd,buf,1024,0))) < 0)  printf( "错误\n"); 	

	printf( "log1\n");
	return flag;
}
int Account_login_persistence(loginnode log,int fd)    //登录
{
	char buf[1024];
	printf( "登录\n");
	int re;
        int flag = 0;
        MYSQL_FIELD * field;
        MYSQL_ROW row;
        MYSQL_RES *result = NULL;
        mysql_query(&mysql,"select account,password,id from login ");
        result = mysql_store_result(&mysql);//将查询的全部结果读取到客户端
	//if(result == NULL)   printf( "111\n");
	while(row = mysql_fetch_row(result))
	{
	//	printf( "%s\t",row[0]);
		if(strcmp(log.account,row[0]) == 0 && strcmp(log.password,row[1]) == 0)  //在数据库里查找是否 有账号和密码
		{
			flag = 1;
			memcpy(&log.id,row[2],sizeof(int));
			break;
		}
	}
	printf( "登录  flag = %d\n",flag);
	log.result = flag;
        memset(buf,0,1024);    //初始化
        memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
        if((re = (send(fd,buf,1024,0))) < 0)  printf( "错误\n"); 	

	printf( "re = %d\n",re);
//	printf( "password = %s\n",log.updata_or_foundpassword);


	return flag;
}
int Account_updatapassword_persistence(loginnode log,int fd)
{        
	char data[1000];
	int flag = 0;
	int re;
	char buf[1024];
        MYSQL_FIELD * field;
        MYSQL_ROW row;
        MYSQL_RES *result = NULL;
        mysql_query(&mysql,"select account,password from login ");
        result = mysql_store_result(&mysql);//将查询的全部结果读取到客户端
	if(NULL == result)   printf( "111\n");
	while(row = mysql_fetch_row(result))
	{
		printf( "%s\t",row[0]);
		if(strcmp(log.account,row[0]) == 0 && strcmp(log.password,row[1]) == 0)  //如果账号和密码匹配
		{
			sprintf(data,"update login set password = '%s' where account = '%s'",log.updata_or_foundpassword,log.account);
			mysql_query(&mysql,data);  //执行成功返回false  ,失败返回true
			flag = 1;

		}
	}

	log.result = flag;
        memset(buf,0,1024);    //初始化
        memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
        if((re = (send(fd,buf,1024,0))) < 0)  printf( "错误\n"); 	

	printf( "updata flag = %d\n",flag);
	return flag;

}
int Account_foundpassword_persistence(loginnode log,int fd)
{
	int re = 0;
        int flag = 0;
        MYSQL_FIELD * field;
        MYSQL_ROW row;
        MYSQL_RES *result = NULL;
	char buf[1024];
        mysql_query(&mysql,"select account,password,phonenumber,friendname from login ");
        result = mysql_store_result(&mysql);//将查询的全部结果读取到客户端
	while(row = mysql_fetch_row(result))
	{
		printf( "%s\t",row[0]);
		if(strcmp(log.account,row[0]) == 0)  //在数据库里查找是否 有账号和密码
		{
			if(strcmp(log.friendname,row[3]) == 0 ||strcmp(log.phonenumber,row[2]) == 0)
			{
				flag = 1;
				strcpy(log.updata_or_foundpassword,row[1]);
				break;
			}
		}
	}
	log.result = flag;
        memset(buf,0,1024);    //初始化
        memcpy(buf,&log,sizeof(loginnode));    //将结构体的内容转为字符串
        if((re = (send(fd,buf,1024,0))) < 0)  printf( "错误\n"); 	

	printf( "re = %d\n",re);
	printf( "password = %s\n",log.updata_or_foundpassword);
	return flag;
}
static void do_write(int epfd,int fd,char *buf)
{

}
void my_err(const char * err_string,int line)
{
	fprintf(stderr,"line : %d ",line);
	perror(err_string);
}

/*
int judge_account_byID(loginnode log)
{
	int flag = 0;
	MYSQL_FIELD * field;
	MYSQL_ROW row;
	MYSQL_RES *result = NULL;
	mysql_query(&mysql,"select ID from login ");
	result = mysql_store_result(&mysql);//将查询的全部结果读取到客户端
	//while(field = mysql_fetch_field(result))
	{
//		if(strcmp("ID",field->name) == 0)
		{
			while(row = mysql_fetch_row(result))
			{
				printf( "%s\t",row[0]);
				if(strcmp(log.number,row[0]) == 0)
				{
					flag = 1;     //已经存在这个 id
				}
			}
		}
	}

	return flag;

}
*/
void send_data(int conn_fd,const char *string)
{
	int ret;
	if((ret = (send(conn_fd,string,1024,0))) < 0)   my_err("send",__LINE__);
//	printf( "re3t = %d\n",ret);
//	printf( "string = %d\n",strlen( string));
}

int command_analy_flag(char a[5])    //用来解析flag
{
        int flag;
        memcpy(&flag,a,sizeof(int));
        return flag;
}
int Modity_information(informationnode inf,int fd)
{

}
