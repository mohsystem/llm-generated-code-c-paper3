#include <stdio.h>

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main() {
    // Test cases
    printf("GCD of 32 and 20 is: %d\n", gcd(32, 20));  // Output: 4
    printf("GCD of 98 and 70 is: %d\n", gcd(98, 70));  // Output: 14
    printf("GCD of 399 and 437 is: %d\n", gcd(399, 437));  // Output: 19
    printf("GCD of 12 and 15 is: %d\n", gcd(12, 15));  // Output: 3
    printf("GCD of 7 and 11 is: %d\n", gcd(7, 11));  // Output: 1
    return 0;
}