#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int digPow(int n, int p) {
    char nStr[20]; // Adjust size as needed
    sprintf(nStr, "%d", n);
    int len = strlen(nStr);
    long long sum = 0;
    for (int i = 0; i < len; i++) {
        sum += pow(nStr[i] - '0', p + i);
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
     printf("%d\n", digPow(114, 3));
    return 0;
}