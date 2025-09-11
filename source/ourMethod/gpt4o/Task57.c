#include <stdio.h>
#include <stdlib.h>

long long factorial(int n) {
    if (n < 0) {
        fprintf(stderr, "Negative numbers are not allowed.\n");
        exit(EXIT_FAILURE);
    }
    long long result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    printf("%lld\n", factorial(0));  // 1
    printf("%lld\n", factorial(1));  // 1
    printf("%lld\n", factorial(5));  // 120
    printf("%lld\n", factorial(10)); // 3628800
    printf("%lld\n", factorial(15)); // 1307674368000
    return 0;
}