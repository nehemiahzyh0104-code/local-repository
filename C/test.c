#include <stdio.h>

int condi = 1;

int
main ()
{
    for(int i =1,i<5,i++){
        printf("TEST");
    }
    int i = '4';
    switch (i)
        {
        case '*':
            printf ("This is *");
            break;
        default:
            printf ("Invalid Operator");
            break;
        case '+':
            printf ("This is +");
            break;
        case '-':
            printf ("This is -");
            break;
        }
}
