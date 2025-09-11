#include <stdio.h>
#include <stdlib.h> // for abs

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a); // Ensure non-negative result
}

int main() {
    printf("%d\n", gcd(48, 18)); // 6
    printf("%d\n", gcd(56, 98)); // 14
    printf("%d\n", gcd(101, 103)); // 1
    printf("%d\n", gcd(123456, 789012)); // 12
    printf("%d\n", gcd(270, 192)); // 6
    return 0;
}