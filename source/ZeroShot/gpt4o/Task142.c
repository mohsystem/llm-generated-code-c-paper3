#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    printf("%d\n", gcd(48, 18)); // 6
    printf("%d\n", gcd(56, 98)); // 14
    printf("%d\n", gcd(101, 103)); // 1
    printf("%d\n", gcd(20, 8)); // 4
    printf("%d\n", gcd(270, 192)); // 6
    return 0;
}