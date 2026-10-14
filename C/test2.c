#include <stdio.h>

void reverse(int a[], int n)
{
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        int t = a[i];
        a[i] = a[j];
        a[j] = t;
    }
}

int main()
{
    int a[] = {1,2,3};
    int n = sizeof(a) / sizeof(a[0]);
    reverse(a, n);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}
