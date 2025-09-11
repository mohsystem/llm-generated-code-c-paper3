#include <stdio.h>
#include <math.h>
#include <string.h>

int findK(int n, int p) {
    char str[100];
    sprintf(str, "%d", n);
    long long sum = 0;
    for (int i = 0; i < strlen(str); i++) {
        sum += (long long) (str[i] - '0') * (long long) pow(str[i] - '0', p + i);
    }
    if (sum % n == 0) {
        return sum / n;
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