#include <stdio.h>
#include <string.h>
#include <math.h>

int digPow(int n, int p) {
    char nStr[20]; // Adjust size as needed
    sprintf(nStr, "%d", n);
    long long sum = 0;
    for (int i = 0; i < strlen(nStr); i++) {
        int digit = nStr[i] - '0';
        sum += pow(digit, p + i);
    }
    if (sum % n == 0) {
        return (int)(sum / n);
    } else {
        return -1;
    }
}

int main() {
    printf("%d\n", digPow(89, 1)); // Expected 1
    printf("%d\n", digPow(92, 1)); // Expected -1
    printf("%d\n", digPow(695, 2)); // Expected 2
    printf("%d\n", digPow(46288, 3)); // Expected 51
    printf("%d\n", digPow(123, 3)); // Expected -1
    return 0;
}