#include<readline/history.h>
#include<stdlib.h>
#include<readline/readline.h>

int main( )
{
	while(1)
	{
		
		char *str = readline("myshell");
		add_history(str);
		free(str);
	}
}
