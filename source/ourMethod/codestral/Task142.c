#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    printf("%d\n", gcd(48, 18)); // Output: 6
    printf("%d\n", gcd(65, 35)); // Output: 5
    printf("%d\n", gcd(12, 8)); // Output: 4
    printf("%d\n", gcd(27, 9)); // Output: 9
    printf("%d\n", gcd(10, 1)); // Output: 1
    return 0;
}