#include<stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    printf("%d\n", gcd(36, 60)); // 12
    printf("%d\n", gcd(100, 50)); // 50
    printf("%d\n", gcd(7, 9)); // 1
    printf("%d\n", gcd(24, 36)); // 12
    printf("%d\n", gcd(15, 15)); // 15
    return 0;
}