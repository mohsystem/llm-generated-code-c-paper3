#include <stdio.h>
#include <stdlib.h>

long long factorial(int num) {
    if (num < 0) {
        fprintf(stderr, "Number must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    long long result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}

int main() {
    printf("%lld\n", factorial(0)); // 1
    printf("%lld\n", factorial(1)); // 1
    printf("%lld\n", factorial(5)); // 120
    printf("%lld\n", factorial(10)); // 3628800
    printf("%lld\n", factorial(20)); // 2432902008176640000
    return 0;
}