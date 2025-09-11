#include<stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    printf("%d\n", gcd(48, 18));  // Output: 6
    printf("%d\n", gcd(100, 50)); // Output: 50
    printf("%d\n", gcd(35, 20));  // Output: 5
    printf("%d\n", gcd(60, 72));  // Output: 12
    printf("%d\n", gcd(12, 18));  // Output: 6
    return 0;
}