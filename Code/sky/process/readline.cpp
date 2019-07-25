#include<iostream>
#include<readline/readline.h>
#include <readline/history.h>
using namespace std;

int main() {

    int i = 0;


    /* read_history("./history"); */
    
    /* HIST_ENTRY **his; */

    /* his = history_list(); */

    while(1)
    {
    printf("$$$$");
    char *input = readline("\t"); 

    printf("%s\n",input);

    add_history(input);
    }
    /* while(his[i] != NULL) */
    /* { */
        /* printf("\001%s\n\002",his[i++]->line); */
    /* } */

    /* write_history("./history"); */

    /* printf("\001\n"); */
    /* read_history("./history"); */
    return 0;
}
