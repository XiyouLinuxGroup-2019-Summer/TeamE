#include<iostream>
#include<readline/readline.h>

using namespace std;

int main() {
    char *a  ;

    char *input = readline(a); 

    printf("%s\n",input);

    return 0;
}
