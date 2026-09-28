#include <stdio.h>

char
upper(char a){
    return (a>= 'a' && a<= 'z') ? a-('a'-'A'):a;
}

int
main ()
{
    char c = 'n';
    printf("%c",upper(c));
    return 0;
}
