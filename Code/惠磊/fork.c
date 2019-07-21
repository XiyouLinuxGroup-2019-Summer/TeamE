#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

int main(void)
{
	pid_t pid;

	printf( "Process Creation Study\n");
	pid = fork();
	switch(pid)
	{
		case 0 :	printf( "this is the child process ID is%d  parent process ID is %d\n",getpid(),getppid()); break;
		default:  printf( "this is the parent process ID is %d  parnent process ID is %d\n",getpid(),getppid( )); break;
		case -1 :	printf( "error\n"); break;
	}


}
