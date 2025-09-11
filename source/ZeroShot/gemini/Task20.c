#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long digPow(int n, int p) {
    int temp = n;
    int numDigits = 0;
    while(temp > 0) {
        numDigits++;
        temp /= 10;
    }

    int *digits = (int *)malloc(numDigits * sizeof(int));
    temp = n;
    for(int i = numDigits - 1; i >= 0; i--) {
        digits[i] = temp % 10;
        temp /= 10;
    }

    long long sum = 0;
    for (int i = 0; i < numDigits; i++) {
        sum += pow(digits[i], p);
        p++;
    }
    free(digits);

    if (sum % n == 0) {
        return sum / n;
    } else {
        return -1;
    }
}

int main() {
    printf("%lld\n", digPow(89, 1)); // 1
    printf("%lld\n", digPow(92, 1)); // -1
    printf("%lld\n", digPow(695, 2)); // 2
    printf("%lld\n", digPow(46288, 3)); // 51
    printf("%lld\n", digPow(123, 4)); // -1

    return 0;
}