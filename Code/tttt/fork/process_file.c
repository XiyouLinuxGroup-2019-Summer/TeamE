#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>


int main(int argc,char ** argv)
{
	int fd = open("temp",O_CREAT | O_RDWR,0664);

	if(fd == -1)
	{
		perror("open error\n");
		exit(1);
	}

	pid_t pid = fork();
	if(pid == -1)
	{
		perror("fork error\n");
		exit(1);
	}

	if(pid > 0)
	{
		char *p = "TTTTTTTTTTTTTT";
		write(fd,p,strlen(p) + 1);
		close(fd);
	//	sleep(2);   //让父进程睡眠 2秒  ,避免父进程先于 子进程死亡
	}
	else if (pid == 0)
	{
		//睡眠一秒保证父进程已经完成了文件的写操作
		sleep(1);
		char buf[1024];
		lseek(fd,0,SEEK_SET);   //需要将 fd 重新定位  虽然将父进程的文件描述符关闭,但 当fork一次后 fd 还没有关掉,指向父进程操作玩的地方
		int len = read(fd,buf,sizeof(buf));

		printf( "%s\n",buf);

		close(fd);

	}
	
	return 0;

}
