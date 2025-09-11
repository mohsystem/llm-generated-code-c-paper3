#include <stdio.h>

int gcd(int a, int b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main() {
    int testCases[][2] = {
        {98, 56},
        {48, 18},
        {399, 437},
        {32, 20},
        {81, 153}
    };

    for (int i = 0; i < 5; ++i) {
        int a = testCases[i][0];
        int b = testCases[i][1];
        printf("GCD of %d and %d is %d\n", a, b, gcd(a, b));
    }

    return 0;
}