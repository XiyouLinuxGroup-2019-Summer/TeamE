#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include "my_recv.h"
#include <stdlib.h>

#define BUFSIZE 1024


//错误处理函数
void my_err(const char *s,int line)
{
    fprintf(stderr,"line:%d",line);
    perror(s);
    exit(1);
}

//从套接字上读取一次数据
int my_recv(int conn_fd,char *data_buf,int len)
{
    static char recv_buf[BUFSIZE] ;//自定义缓冲区
    static char *pread; //指向下一次数据读取位置
    static int len_remain = 0;//自定义缓冲区中剩余字节数
    int i ; 

    //如果缓冲区中没有数据，则从套接字中读取数据
    if(len_remain <= 0)
    {
        if((len_remain = recv(conn_fd,recv_buf,sizeof(recv_buf),0)) < 0)
            my_err("recv",__LINE__);
        else if(len_remain == 0)//目的计算机的socket 连接关闭
        {
            printf("读取失败\n");
            return 0;
        }

        pread = recv_buf; //重新初始化pread指针
    }


    //从自定义缓冲区中读取一次数据
    for(i = 0;*pread != '\n';i++)
    {//防止指针越界
        if(i > len) return -1;

        data_buf[i] = *pread++;
        len_remain--;
    }
    /* printf("接收到的数据是:%s\n",data_buf); */

    //去除标志
    len_remain--;
    pread++;

    return i;//读取成功
}
