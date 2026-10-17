#include <stdio.h>

void
fac (int i)
{
    if (i != 0)
        {
            putchar (i);
        }
    else
        {
            fac (i % 10);
        }
}

int
main ()
{
    fac (114);
    return 0;
}
