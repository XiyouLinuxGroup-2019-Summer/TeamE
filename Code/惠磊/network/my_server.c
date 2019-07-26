#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<error.h>
#include"my_recv.h"   //自定义头文件

#define SERV_PORT   4507  //     服务器的端口
#define LISTENQ 12        //连接请求队列的最大长度

#define INVALID_USERINFO 'n'  //用户信息无效
#define VALID_USERINFO 'y'   //用户信息有效

#define USERNAME 0   //接受到的是用户名
#define PASSWORD 1    //接受到的密码

struct userinfo   //保存用户名和密码的结构体
{
	char username[32];
	char password[32];
};


struct userinfo users[] = {
	{"linux","unix"},
	{"4507","4508"},
	{"clh","clh"},
	{"xl","xl"},
	{" "," "}  //以只含一个空格的字符串作为数组的结束标志
};

int main( )
{
	int sock_fd,conn_fd;
	int optval;
	int flag_recv = USERNAME;   //标识 接受到的是用户名还是密码
	int ret;
	int name_num;
	pid_t pid;
	socklen_t cli_len;
	struct sockaddr_in cli_addr,serv_addr;

	char recv_buf[128];

	//创建一个TCP套接字
	//AF_INET : 使用IPva4 TCP/IP 协议
	//SOCK_STREAM : 创建TCP流套接字 
	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd < 0)   my_err("setsockopt",__LINE__);
	
	//setsockopt   设置套接字的属性
	//设置该套接字使之可以重新绑定端口
	//SO_REUSEADDR    套接字选项的名称
	optval = 1;
	if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)   my_err("setsockopt",__LINE__);

	//初始化服务器端地址结构
	memset(&serv_addr,0,sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT); //设置端口号
	serv_addr.sin.s_addr = htonl(INADD_ANY);    //设置地址   INADD_ANY 是本地地址

	//将套接字绑定到本地端口
	if(bind(sock_fd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in)) < 0)   my_err("bind",__LINE__);

	//将套接字转化为监听套接字
	if(listen(sock_fd,LISTENQ) < 0)    my_err("listen",__LINE__);
	//LISTENQ   为最大的连接数
	
	cli_len = sizeof(struct sockaddr_in);

	while(1)  //通过accept 接受客户端的链接请求,并返回连接套接字用于收发数据
	{
		//fd 是经socket 创建经函数bind绑定到本地某一端口上,然后经过函数listen转化而来的套接字
		//cli_addr 用来保存发起连接请求的主机的地址和端口
		conn_fd = accept(sock_fd,(struct sockaddr *)&cli_addr,&cli_len);
		if(conn_fd < 0)  my_err("accept",__LINE__);
		printf("accept a new client,ip: %s \n",inet_ntoa(cli_addr.sin_addr));
		
		//创建一个子进程处理刚刚收到的连接请求,并返回连接套接字用于收发数据
		if((pid = fork()) == 0)	//子进程
		{

		}
	}
	

	

}
