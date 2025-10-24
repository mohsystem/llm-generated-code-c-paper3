#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 * Finds a positive integer k, if it exists, such that the sum of the digits of n
 * raised to consecutive powers starting from p is equal to k * n.
 *
 * @param n A positive integer.
 * @param p A positive integer.
 * @return The positive integer k, or -1 if it does not exist.
 */
long long digPow(int n, int p) {
    // Determine buffer size for string conversion
    int len = snprintf(NULL, 0, "%d", n);
    char *s = (char*)malloc(len + 1);
    if (s == NULL) {
        // Handle memory allocation failure
        return -1; 
    }
    snprintf(s, len + 1, "%d", n);

    long long sum = 0;
    for (int i = 0; i < len; ++i) {
        int digit = s[i] - '0';
        sum += (long long)pow((double)digit, (double)(p + i));
    }

    free(s);

    if (sum > 0 && sum % n == 0) {
        return sum / n;
    } else {
        return -1;
    }
}

int main() {
    // Test Case 1
    printf("%lld\n", digPow(89, 1));
    // Test Case 2
    printf("%lld\n", digPow(92, 1));
    // Test Case 3
    printf("%lld\n", digPow(695, 2));
    // Test Case 4
    printf("%lld\n", digPow(46288, 3));
    // Test Case 5
    printf("%lld\n", digPow(1, 1));

    return 0;
}