#include <stdio.h>
#include <stdlib.h>

long factorial(int number) {
    if (number < 0) {
        fprintf(stderr, "Number must be non-negative.\n");
        exit(EXIT_FAILURE);
    }
    long result = 1;
    for (int i = 2; i <= number; i++) {
        result *= i;
    }
    return result;
}

int main() {
    printf("%ld\n", factorial(5));  // 120
    printf("%ld\n", factorial(0));  // 1
    printf("%ld\n", factorial(10)); // 3628800
    printf("%ld\n", factorial(3));  // 6
    printf("%ld\n", factorial(1));  // 1
    return 0;
}