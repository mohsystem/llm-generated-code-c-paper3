#include <stdio.h>

int persistence(long long num) {
    if (num < 0) {
        return -1; /* invalid input */
    }
    int count = 0;
    while (num >= 10) {
        long long prod = 1;
        long long n = num;
        while (n > 0) {
            prod *= (n % 10);
            n /= 10;
        }
        num = prod;
        count++;
    }
    return count;
}

int main(void) {
    long long tests[5] = {39, 999, 4, 25, 444};
    for (int i = 0; i < 5; i++) {
        long long t = tests[i];
        int res = persistence(t);
        printf("persistence(%lld) = %d\n", t, res);
    }
    return 0;
}