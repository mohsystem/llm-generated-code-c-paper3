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
    printf("%d\n", gcd(48, 18)); // Expected: 6
    printf("%d\n", gcd(12, 8));  // Expected: 4
    printf("%d\n", gcd(15, 25)); // Expected: 5
    printf("%d\n", gcd(7, 11));  // Expected: 1
    printf("%d\n", gcd(0, 5));   // Expected: 5
    return 0;
}