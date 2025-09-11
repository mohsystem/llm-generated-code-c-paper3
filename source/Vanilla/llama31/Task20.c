#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int findK(int n, int p) {
    int original = n;
    int sum = 0;
    int power = p;
    while (n > 0) {
        int digit = n % 10;
        sum += (int) pow(digit, power);
        n /= 10;
        power++;
    }
    if (sum % original == 0) {
        return sum / original;
    } else {
        return -1;
    }
}

int main() {
    printf("%d\n", findK(89, 1)); // 1
    printf("%d\n", findK(92, 1)); // -1
    printf("%d\n", findK(695, 2)); // 2
    printf("%d\n", findK(46288, 3)); // 51
    printf("%d\n", findK(100, 1)); // -1
    return 0;
}