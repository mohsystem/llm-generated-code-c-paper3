#include <stdio.h>

long long factorial(int num) {
    long long result = 1;
    for (int i = 2; i <= num; i++) {
        result *= i;
    }
    return result;
}

int main() {
    printf("%lld\n", factorial(5));   // Output: 120
    printf("%lld\n", factorial(0));   // Output: 1
    printf("%lld\n", factorial(1));   // Output: 1
    printf("%lld\n", factorial(10));  // Output: 3628800
    printf("%lld\n", factorial(15));  // Output: 1307674368000
    return 0;
}