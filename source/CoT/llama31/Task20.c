#include <stdio.h>
#include <math.h>
#include <string.h>

int findK(int n, int p) {
    char strN[20];
    sprintf(strN, "%d", n);
    long long sum = 0;
    for (int i = 0; i < strlen(strN); i++) {
        sum += (long long) pow(strN[i] - '0', p + i);
    }
    if (sum % n == 0) {
        return (int) (sum / n);
    } else {
        return -1;
    }
}

int main() {
    printf("%d\n", findK(89, 1));  // Expected output: 1
    printf("%d\n", findK(92, 1));  // Expected output: -1
    printf("%d\n", findK(695, 2)); // Expected output: 2
    printf("%d\n", findK(46288, 3)); // Expected output: 51
    printf("%d\n", findK(123, 1)); // Expected output: -1
    return 0;
}