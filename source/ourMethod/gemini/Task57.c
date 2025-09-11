#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

long long factorial(int n) {
    if (n < 0) {
        // In C, we typically return an error indicator rather than throwing exceptions.
        errno = EINVAL; // Invalid argument
        return -1; 
    }
    if (n == 0) {
        return 1;
    } else {
        long long result = 1;
        for (int i = 1; i <= n; i++) {
             if (LLONG_MAX / result < i) { // Check for overflow
                errno = ERANGE; // Result out of range
                return -1;
            }
            result *= i;
        }
        return result;
    }
}

int main() {
    printf("%lld\n", factorial(0)); // Expected: 1
    printf("%lld\n", factorial(1)); // Expected: 1
    printf("%lld\n", factorial(5)); // Expected: 120
    printf("%lld\n", factorial(10)); // Expected: 3628800
    printf("%lld\n", factorial(20)); // Expected: 2432902008176640000
    return 0;
}