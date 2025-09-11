#include <stdio.h>
#include <math.h>

int digPow(int n, int p) {
    int originalN = n;
    int sum = 0;
    int length = 0;

    while (n != 0) {
        length++;
        n /= 10;
    }

    n = originalN;

    while (n > 0) {
        int digit = n % 10;
        sum += pow(digit, p);
        n /= 10;
        p++;
    }

    for (int k = 1; k * originalN <= sum; k++) {
        if (k * originalN == sum) {
            return k;
        }
    }

    return -1;
}

int main() {
    printf("%d\n", digPow(89, 1)); // Output: 1
    printf("%d\n", digPow(92, 1)); // Output: -1
    printf("%d\n", digPow(695, 2)); // Output: 2
    printf("%d\n", digPow(46288, 3)); // Output: 51
    return 0;
}