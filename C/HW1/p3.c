#include <stdio.h>

int
main ()
{
    long long inp = 1, max = -99999999999, sum = 0;
    do
        {
            scanf ("%lld", &inp);
            sum += inp;
            if (inp == 0)
                {
                    continue;
                }
            else if (inp > max)
                {
                    max = inp;
                }
        }
    while (inp);
    printf ("sum: %lld\n", sum);
    printf ("maximum: %lld\n", max);

    return 0;
}
