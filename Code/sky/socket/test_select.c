#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

void display_time(const char * string)
{
    int seconds;

    seconds = time((time_t*)NULL);
    printf("%s,%d\n",string,seconds);
}
int main()
{
    fd_set readfds;//定义一个文件描述符集合
    struct timeval timeout;//定义阻塞时间
    int ret;

    //监视文件描述符0是否有输入，0表示标准输入，1表示标准输出
    FD_ZERO(&readfds);//开始使用文件描述符集合前一般要进行清空
    FD_SET(0,&readfds);//将标准输入文件加入文件描述符集合

    //设置阻塞时间为10秒
    timeout.tv_sec = 10;//秒数 
    timeout.tv_usec = 0;//微妙数

    while(1)
    {
        display_time("before select");//监视前
        ret = select(1,&readfds,NULL,NULL,&timeout);//(需要监视的文件描述符数,需要监视的可读文件描述符集合,需要监视的可写文件描述符集合，异常文件描述集合，阻塞时间)
        display_time("after select");//监视后

        switch(ret)
        {
        case 0:
            printf("No data in ten seconds.\n");
            exit(0);break;
        case -1:
            perror("select");
            exit(0);break;
        default:
            getchar(); //将数据读入否则键盘上一直为读就绪
            printf("Data is avaliable now.\n");
        }
    }
    return 0;
}

