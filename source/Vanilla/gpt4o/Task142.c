#include <stdio.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    printf("%d\n", gcd(48, 18)); // Test case 1
    printf("%d\n", gcd(54, 24)); // Test case 2
    printf("%d\n", gcd(101, 103)); // Test case 3
    printf("%d\n", gcd(56, 98)); // Test case 4
    printf("%d\n", gcd(20, 100)); // Test case 5
    return 0;
}