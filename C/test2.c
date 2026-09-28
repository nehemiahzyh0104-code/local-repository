#include <stdio.h>

int condi = 1;

int
main ()
{
    int i = '4';
    switch (i) {
        case '*':
            printf("This is *");
            break;
        default:
            printf("Invalid Operator");
            break;
        case '+':
            printf("This is +");
            break;
        case '-':
            printf("This is -");
            break;
    }
}
