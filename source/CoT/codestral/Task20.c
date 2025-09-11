#include <stdio.h>
#include <math.h>

int digPow(int n, int p) {
    int sum = 0;
    int temp = n;
    int digits = 0;

    while (temp != 0) {
        digits++;
        temp /= 10;
    }

    temp = n;

    for (int i = 0; i < digits; i++) {
        int digit = temp % 10;
        sum += pow(digit, p + i);
        temp /= 10;
    }

    if (sum % n == 0) {
        return sum / n;
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