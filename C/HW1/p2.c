#include <stdio.h>

int
main ()
{
    int num, sum = 0;

    printf ("How many students are there?\n");
    scanf ("%i", &num);
    printf ("What are their scores?\n");

    int i;
    for (i = 0; i < num; i++)
        {
            int score;
            scanf ("%i", &score);
            sum += score;
        }

    double average = sum * 1.0 / num;
    if (average == 60)
        {
            printf ("Good!\n");
        }
    else if (average > 60)
        {
            printf ("Excellent!\n");
        }
    else
        {
            printf ("Bad!\n");
        }
    printf ("Average score is %.2f.\n", average);

    return 0;
}
