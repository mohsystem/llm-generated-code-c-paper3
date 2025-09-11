#include <stdio.h>
#include <stdint.h>

long long factorial(int n) {
    if (n < 0) {
         // In C, there's no standard exception like std::invalid_argument. Returning -1 to indicate an error.
         return -1; 
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
    printf("%lld\n", factorial(0)); // Output: 1
    printf("%lld\n", factorial(1)); // Output: 1
    printf("%lld\n", factorial(5)); // Output: 120
    printf("%lld\n", factorial(10)); // Output: 3628800
    printf("%lld\n", factorial(20)); // Output: 2432902008176640000
    return 0;
}