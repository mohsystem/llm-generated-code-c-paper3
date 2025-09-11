#include<stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    printf("%d\n", gcd(48, 18)); // Output: 6
    printf("%d\n", gcd(123, 456)); // Output: 3
    printf("%d\n", gcd(7, 7)); // Output: 7
    printf("%d\n", gcd(0, 0)); // Output: 0
    printf("%d\n", gcd(12, 0)); // Output: 12
    return 0;
}