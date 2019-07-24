#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>


int main( )
{
	pid_t pid;
	char *msg;
	int k;
	int exit_code;

	printf( "Study how to get exit code\n");
	pid = fork();

	switch(pid)
	{
		case 0 : 
			msg = "child process is running";
			k = 5;
			break;
		case -1:
			perror("process creatio failed\n");
			exit(1);
		default:
			exit_code = 0;
			break;
	}

	//父子进程都会执行一下这段代码
	//子进程pid 值为 0 ,父进程pid 值为子进程的 ID
	//
	if(pid != 0)   //父进程等待子进程结束
	{
		int stat_val;
		pid_t child_pid;

		child_pid = wait(&stat_val);

		printf( "Child process has exited,pid = %d\n",child_pid);

		if(WIFEXITED(stat_val))   printf( "child exited with cade %d\n",WEXITSTATUS(stat_val));
		else printf( "Child exited abnormally\n");
	}
	else   //子进程暂停 5 秒,在这个过程中可以运行 命令 ps  aux 查看父进程状态
	{
		while(k-- > 0)
		{
			puts(msg);
			sleep(1);
		}
	}

	exit(exit_code);
}
