#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint64_t factorial(int n) {
    if (n < 0) {
         // In C,  returning 0 for error can be ambigious so better to exit. 
         fprintf(stderr, "Factorial is not defined for negative numbers.\n");
         return 0; // Or handle error differently
    }
    if (n == 0) {
        return 1;
    }
    uint64_t result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    printf("%llu\n", factorial(0)); // Output: 1
    printf("%llu\n", factorial(1)); // Output: 1
    printf("%llu\n", factorial(5)); // Output: 120
    printf("%llu\n", factorial(10)); // Output: 3628800
    printf("%llu\n", factorial(20)); // Output: 2432902008176640000
    return 0;
}