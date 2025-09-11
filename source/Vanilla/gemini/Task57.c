#include <stdio.h>

long long factorial(int n) {
    if (n < 0) {
        return -1; // Factorial is not defined for negative numbers
    }
    if (n == 0) {
        return 1;
    }
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    printf("%lld\n", factorial(5));
    printf("%lld\n", factorial(0));
    printf("%lld\n", factorial(10));
    printf("%lld\n", factorial(1));
    printf("%lld\n", factorial(-5));
    return 0;
}