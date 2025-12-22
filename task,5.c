#include <stdio.h>

void swapNumbers(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main() {
    int a = 10, b = 20;

    printf("Before swapping: a = %d, b = %d\n", a, b);

    swapNumbers(&a, &b);

    printf("After swapping: a = %d, b = %d\n", a, b);

    return 0;
}
