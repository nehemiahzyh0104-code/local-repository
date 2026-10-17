#include <stdio.h>

int
main ()
{
    int num, inptp, inptm;
    int n = 0;
    char stp;

    scanf ("%i", &num);

    while (1)
        {
            int check = scanf ("%i %i", &inptm, &inptp);

            if (check == 2)
                {
                    num = num + inptp - inptm;
                    n++;
                }
            else
                {
                    scanf ("%c", &stp);
                    break;
                }
        }

    if (stp == 's')
        {
            printf ("%i", n);
        }
    else if (stp == 'p')
        {
            printf ("%i", num);
        }

    return 0;
}
