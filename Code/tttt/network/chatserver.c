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

#define PORT 4507
#define LISTENQ 20
#define EPOLLLEN 2000
#define BUFSIZE  1024
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


int login(loginnode log);

void printResult(MYSQL *mysqlPrint);
static void do_write(int epfd,int fd,char *buf);
static void do_read(int epfd,int fd,char *buf);
int listenfd_accept(int epfd,int fd);
static void handle_events(int epollfd,struct epoll_event *events,int num,int listenfd,char *buf);
void my_err(const char * err_string,int line);
void send_data(int conn_fd,const char *string);

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


	int ret = 0;
	while(1)
	{
		//委托内核监测事件
		ret = epoll_wait(epfd,events,EPOLLLEN,-1);
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

	printf( "accept a new client : %s : %d \n",inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);
	send_data(clifd,"welcome login my tcp server\n");
	ev.data.fd = clifd;
	ev.events = EPOLLIN;
	//向 fd 进行 add 操作 
	epoll_ctl(epfd,EPOLL_CTL_ADD,clifd,&ev);
	
	return 0;
}

static void do_read(int epfd,int fd,char *buf)
{
	loginnode log;
	int ret;
	int i;           //sizeof(buf)   出错   因为 buf 是个指针,指针一次只有 8 个字节
	memset(buf,0,1024);
	memset(&log,0,sizeof(loginnode));

	if((ret = recv(fd,buf,sizeof(loginnode),0)) < 0)
	{
		my_err("recv",__LINE__);
		close(fd);
	}
	printf( "ret1 = %d\n",ret);
	if(ret == 0)
	{
		printf("client exit\n");
		epoll_ctl(epfd,EPOLL_CTL_DEL,fd,NULL);
	
	}
	buf[ret] = '\0';  //将数据 结束标志 '\n' 替换成 字符串结束标志
//	puts(buf);
	printf( "接受\n");
	memcpy(&log,buf,sizeof(loginnode));
	printf( "name %s\n",log.name);
        printf( "number %s\n",log.number);
        printf( "password %s\n",log.password);
        printf( "phone %s\n",log.phonenumber);
        printf( "frine %s\n",log.friendname);
        printf( "flag = %d\n",log.flag);

	//printf( "log.flag = %d\n",log.flag);
	//printf( "log.name = %s\n",log.name);
	switch(log.flag)
	{
		case 1: login(log);break;
	}
	memset(buf,0,sizeof(buf));
}

int login(loginnode log)
{
	        printf( "name %s\n",log.name);
        printf( "number %s\n",log.number);
        printf( "password %s\n",log.password);
        printf( "phone %s\n",log.phonenumber);
        printf( "frine %s\n",log.friendname);
        printf( "flag = %d\n",log.flag);

	printf( "login\n");

	getchar();

	MYSQL mysql;
        MYSQL_RES *result;
        mysql_init(&mysql);    
        if(!mysql_real_connect(&mysql,"127.0.0.1","root","073848","chat",0,NULL,0))  my_err("conect mysql",__LINE__);
     
	if(mysql_query(&mysql,"set names utf8"))  printf( "FAlse \n");
	char a[1000];						
//	if(!mysql_query(&mysql,"use login")) printf( "false\n");
	sprintf(a,"insert into login values('%s','%s','%s','%s','%s')",log.name,log.number,log.password,log.phonenumber,log.friendname);
//	snprintf(a,sizeof(a),log.name,log.number,log.password,log.phonenumber,log.friendname);

	
	if(mysql_query(&mysql,a))   printf( "false\n");
	mysql_query(&mysql,"select *from login");
	printResult(&mysql);


	printf( "log1\n");
}
static void do_write(int epfd,int fd,char *buf)
{

}
void my_err(const char * err_string,int line)
{
	fprintf(stderr,"line : %d ",line);
	perror(err_string);
}

void send_data(int conn_fd,const char *string)
{
	int ret;
	if((ret = (send(conn_fd,string,strlen(string) + 1,0))) < 0)   my_err("send",__LINE__);
	printf( "re3t = %d\n",ret);
	printf( "string = %d\n",strlen( string));
}

void printResult(MYSQL *mysqlPrint)//打印结果集(此处传入指针，而非内容)
{
    MYSQL_RES * result;
    int numFields = 0;
    int numRows = 0;
    MYSQL_FIELD * field;
    MYSQL_ROW row;
    int i = 0;
    result = mysql_store_result(mysqlPrint);//将查询的全部结果读取到客户端
    if(NULL == result)   printf( "error\n");

    numFields = mysql_num_fields(result);//统计结果集中的字段数
    numRows = mysql_num_rows(result);//统计结果集的行数
    while(row = mysql_fetch_row(result))//返回结果集中的列信息(字段)
        for(i = 0;i < numFields;i++)
	    printf("%s\t", row[i]);
    printf("\n");
    if(result)
    {   
        while(row = mysql_fetch_row(result))//返回结果集中行的记录
        {   
            for(i = 0; i < numFields; i++)
            {   
                printf("%s\t", row[i]);                                                                                                                  
            }   
            printf("\n");
        }   
    }   
    mysql_free_result(result);//释放result空间，避免内存泄漏
}

