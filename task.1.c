
#include <stdio.h>

int main() {
    int num = 10;
    int *ptr = &num;

    printf("Value of num: %d\n", num);
    printf("Value stored in ptr (address of num): %p\n", ptr);
    printf("Address of num: %p\n", &num);
    printf("Value accessed using *ptr: %d\n", *ptr);

    return 0;
    }

