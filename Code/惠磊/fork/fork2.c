//验证父子进程是随机执行的,不确定

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(void)
{
	pid_t pid;
	char *msg;
	int k;


	printf( "Process Creation Study\n");
	pid = fork();
	switch(pid)
	{
		case 0: msg = "child process is running"; 
			k = 3;
			break;
		//返回-1 通常是因为父进程拥有的子进程的个数超过了规定的限制
		case -1:perror("Process creation failed\n"); break;
		default:
			msg = "parent process is running";
			k = 5;
			break;
	}

	while(k > 0)
	{
		puts(msg);
		sleep(1);
		k--;
	}

	exit(0);
}
