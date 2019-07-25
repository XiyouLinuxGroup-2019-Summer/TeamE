#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    char  buffer[32];
    int ret = 0;
    int host = 0;//主机地址
    int network = 0;
    unsigned int address = 0;
    struct in_addr in;//IP地址结构体
    
    in.s_addr = 0;
    printf("请输入你的IP地址:");
    fgets(buffer,31,stdin);
    buffer[31] = '\0';

    //inet_aton //address to net
    if((ret = inet_aton(buffer,&in)) == 0)
        printf("inet_aton:\t 不合法地址\n");
    else printf("inet_aton:\t0x%x\n",in.s_addr);
    
    //inet_addr过时函数
    if((address = inet_addr(buffer)) == INADDR_NONE)
        printf("inet_addr:\t 不合法地址\n");
    else printf("inet_addr:\t0x%x\n",address);

    //inet_network 将网络地址转换成主机字节顺序的二进制形式
    if((address = inet_network(buffer)) == -1)
        printf("inet_network:\t不合法地址\n");
    else printf("inet_network:\t0x%x\n",address);

    //inet_ntoa 将网络字节序转换为.分割的字符串形式
    if(inet_ntoa(in) == NULL)
        printf("inet_ntoa:\t 不合法地址\n");
    else printf("inoet_ntoa:\t%s\n",inet_ntoa(in));

    //inet_lnaof()和inet_netof()函数
    host = inet_lnaof(in);//从in中提取主机号
    network = inet_netof(in);//从in中提取网路号

    printf("主机地址:\t0x%x\n",host);
    printf("网络地址:\t0x%x\n",network);

    in = inet_makeaddr(network,host); //主机+网路 =  网路地址
    printf("拼接后网络地址为:0x%x\n",in.s_addr);
    return 0;
}

