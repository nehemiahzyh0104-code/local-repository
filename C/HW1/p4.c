#include <stdio.h>

int
main ()
{
    int max, scd, min, scdm;

    int seq;
    scanf ("%i", &seq);

    int num;

    scanf ("%i", &num);
    max = num, min = num,scd=num,scdm=num;

    for (int n = 1; n < seq; n++)
        {
            scanf ("%i", &num);

            if (num > max)
                {
                    scd = max;
                    max = num;
                }
            else if (num < max && (scd==max||num>scd))
                {
                    scd = num;
                }

            if (num < min)
                {
                    scdm = min;
                    min = num;
                }
            else if (num > min && (scdm==min||num<scdm))
                {
                    scdm = num;
                }
        }

    printf ("%i %i", scd, scdm);

    return 0;
}
