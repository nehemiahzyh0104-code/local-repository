#include <stdio.h>

int
main (void)
{
    int n;
    scanf ("%d", &n);

    double para[30];
    for (int i = 0; i <= n; i++)
        {
            scanf ("%lf", &para[i]);
        }

    int m;
    scanf ("%d", &m);

    for (int k = 0; k < m; k++)
        {
            double x;
            scanf ("%lf", &x);

            double opt = para[n];
            for (int i = n - 1; i >= 0; i--)
                {
                    opt = opt * x + para[i];
                }
            printf ("%.3lf\n", opt);
        }

    return 0;
}
