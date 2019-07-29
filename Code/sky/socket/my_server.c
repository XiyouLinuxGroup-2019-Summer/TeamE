#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <memory.h>
#include <stdlib.h>
#include "my_recv.h"

#define SERV_PORT 4570 //服务器端的地址
#define LISTENQ 12     //链接请求队列的最大长度

#define INVALID_USERINFO //用户信息无效
#define VALID_USERINFO   //用户信息有效

#define USERNAME 0       //接受到的是密码
#define PASSWD   1       //接收到的是用户名

struct userinfo
{//保存用户名和密码的结构体
    char username[32];
    char passwd[32];

};

struct userinfo user[]=
{
    {"123","123"},{" "," "}
};
//查找用户名是否存在
int find_name(const char *name)
{

    if(name == NULL)
    {
        printf("int find_name,NULL,pointer");
        return -2;
    }

    for(int i = 0;user[i].username[0] != ' '; i++)
    {
        if(strcmp(user[i].username,name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void send_data(int conn_fd,const char *string)
{
    if(send(conn_fd,string,strlen(string),0) < 0)
        my_err("send",__LINE__);

}
int main()
{
    int sock_fd,conn_fd; //服务器套接字描述符，客户端套接字文件描述符号
    int optval;          //
    int flag_recv = USERNAME; //标记接受到的是什么
    int ret;                  //接收到的数据字节数
    int name_num ;            //
    pid_t pid;                //子进程ID
    socklen_t cli_len ;       //
    struct sockaddr_in cli_addr,serv_addr;  //TCP/IP协议地址
    char recv_buf[128];

    //创建一个TCP套接字
    sock_fd = socket(AF_INET,SOCK_STREAM,0);  //(协议族，套接字类型，0)  返回新创建的套接字的描述符
    if(sock_fd < 0) my_err("socket",__LINE__); //自定义错误处理函数

    //设置该套接字，使其可以重新绑定端口
    optval = 1;
    if(setsockopt(sock_fd,SOL_SOCKET,SO_REUSEADDR,(void *)&optval,sizeof(int)) < 0)
       //(描述符，套接字选项操作层次，选项名字，选项，选型长度)
        my_err("setsockopt",__LINE__);
    
    //初始化服务器端地址结构
    memset(&serv_addr,0,sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;       //地址类型
    serv_addr.sin_port = htons(SERV_PORT);//端口号
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//IP地址

    //将套接字绑定到本地端口
    if(bind(sock_fd,(struct sockaddr *)&serv_addr,sizeof(struct sockaddr_in)) < 0)
        my_err("bind",__LINE__);

    //将套接字转化为监听套接字
    if(listen(sock_fd,LISTENQ) < 0)
        my_err("listen",__LINE__);

   cli_len = sizeof(struct sockaddr_in); 
    while(1)
    {
        //通过accpet接受客户端的连接请求，返回客户端的套接字用于收发数据
        conn_fd = accept(sock_fd,(struct sockaddr*)&cli_addr,&cli_len);
        //(监听套接字，地址和端口，大小)
        if(conn_fd  < 0)
            my_err("accept",__LINE__);
       
        //打印连接信息
        printf("收到一个新的客户端的连接请求 IP:%s\n",inet_ntoa(cli_addr.sin_addr));
        
        //创建一个子进程处理刚刚接受到的连接请求
        if((pid = fork()) == 0)
        {//子进程
            if((ret = recv(conn_fd,recv_buf,sizeof(recv_buf),0)) < 0)
            //(客户端套接字，缓冲区，长度，控制选项)
            {
                perror("recv");
                exit(1);
            }
            recv_buf[ret-1] = '\0';
            
            if(flag_recv == USERNAME)
            {//接受到的是用户名
                name_num =  find_name(recv_buf);
                switch(name_num)
                {
                    case -1://
                        send_data(conn_fd,"n\n");
                        break;
                    case -2:
                        exit(1);
                        break;
                    default:
                        send_data(conn_fd,"y\n");
                        flag_recv = PASSWD;
                        break;

                }

            }
        }
    }
    return 0;
}

