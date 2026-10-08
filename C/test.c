#include <stdio.h>

int
main ()
{
    int a[2]={1,2};
    int (*p)[2]=&a;
    
    printf("%i",(*p)[1]);
    return 0;
}
