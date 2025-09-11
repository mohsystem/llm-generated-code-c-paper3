#include <stdio.h>

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main() {
    printf("GCD of 98 and 56 is %d\n", gcd(98, 56));
    printf("GCD of 48 and 18 is %d\n", gcd(48, 18));
    printf("GCD of 399 and 437 is %d\n", gcd(399, 437));
    printf("GCD of 32 and 20 is %d\n", gcd(32, 20));
    printf("GCD of 81 and 153 is %d\n", gcd(81, 153));
    return 0;
}