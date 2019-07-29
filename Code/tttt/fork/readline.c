#include<stdlib.h>
#include<readline/readline.h>

int main(void)
{
	while(1)
	{
		char *str = readline("myshell$");
		free(str);
	}
}
