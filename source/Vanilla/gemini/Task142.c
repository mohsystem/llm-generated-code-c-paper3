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
    printf("%d\n", gcd(48, 18)); // Output: 6
    printf("%d\n", gcd(12, 8));  // Output: 4
    printf("%d\n", gcd(15, 25)); // Output: 5
    printf("%d\n", gcd(7, 13));  // Output: 1
    printf("%d\n", gcd(100, 50));// Output: 50
    return 0;
}