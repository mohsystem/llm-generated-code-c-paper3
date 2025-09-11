#include <stdio.h>
#include <stdlib.h>

long long factorial(int n) {
    if (n < 0) {
        fprintf(stderr, "Number must be non-negative.\n");
        exit(EXIT_FAILURE);
    }
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    printf("%lld\n", factorial(5));  // 120
    printf("%lld\n", factorial(10));  // 3628800
    printf("%lld\n", factorial(0));  // 1
    printf("%lld\n", factorial(1));  // 1
    // There is no good way to handle errors in C, so we just exit the program.
    factorial(-1);  // prints "Number must be non-negative." and exits
    return 0;
}