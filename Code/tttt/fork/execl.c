#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

int main( )
{
	pid_t pid;
	pid = fork();

	if(pid == 0)
	{
		execl("for_fork"," ","-al",NULL);
	}
}

