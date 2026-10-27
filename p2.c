#include <stdio.h>
#include <stdlib.h>

int
palic (char *pali, int m)
{
    if (m % 2) // even
        {
            for (int i = 0; i < m / 2; i++)
                {
                    if (pali[i] != pali[m - 1 - i])
                        {
                            return 0;
                        }
                }
        }

    else
        {
            for (int i = 0; i < (m - 1) / 2; i++)
                {
                    if (pali[i] != pali[m - 1 - i])
                        {
                            return 0;
                        }
                }
        }

    return 1;
}

int
main (void)
{
    int n = 0;
    scanf ("%d", &n);

    for (int i = 0; i < n; i++)
        {
            int m = 0;
            scanf ("%d", &m);
            char *pali = malloc (sizeof (char) * (m + 1));
            scanf ("%s", pali);

            int k = palic (pali, m);
            if (k)
                {
                    printf ("Yes\n");
                }
            else
                {
                    printf ("No\n");
                }

            free (pali);
        }

    return 0;
}
