#include <stdio.h>

int main(void) {
    int x, y;

    if (scanf("%d %d", &x, &y) != 2) {
        return 1;
    }

    printf("%d", x + y);
    return 0;
}
