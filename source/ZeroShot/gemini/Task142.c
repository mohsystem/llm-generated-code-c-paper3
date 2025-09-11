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
    printf("%d\n", gcd(12, 18)); // Output: 6
    printf("%d\n", gcd(48, 18)); // Output: 6
    printf("%d\n", gcd(17, 23)); // Output: 1
    printf("%d\n", gcd(0, 5)); // Output: 5
    printf("%d\n", gcd(10, 0)); // Output: 10
    return 0;
}