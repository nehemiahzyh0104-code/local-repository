#include <stdio.h>

int
main (void)
{
    int n;
    scanf ("%d", &n);

    double para[n + 1];
    for (int i = 0; i <= n; i++)
        {
            scanf ("%lf", &para[i]);
        }

    int m;
    scanf ("%d", &m);

    double point[m];
    for (int i = 0; i < m; i++)
        {
            scanf ("%lf", &point[i]);
        }

    int k = 0;
    do
        {
            double opt = para[n];
            for (int i = n - 1; i >= 0; i--)
                {
                    opt = opt * point[k] + para[i];
                }
            printf ("%.3lf\n", opt);
            k++;
        }
    while (k < m);

    return 0;
}
