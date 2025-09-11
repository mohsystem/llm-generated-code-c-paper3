#include <stdio.h>
#include <math.h>
#include <string.h>

int findFunnyNumber(int n, int p) {
    char numStr[12];
    snprintf(numStr, 12, "%d", n);
    int sum = 0;

    for (int i = 0; i < strlen(numStr); i++) {
        int digit = numStr[i] - '0';
        sum += pow(digit, p + i);
    }

    if (sum % n == 0) {
        return sum / n;
    } else {
        return -1;
    }
}

int main() {
    printf("%d\n", findFunnyNumber(89, 1));    // 1
    printf("%d\n", findFunnyNumber(92, 1));    // -1
    printf("%d\n", findFunnyNumber(695, 2));   // 2
    printf("%d\n", findFunnyNumber(46288, 3)); // 51
    printf("%d\n", findFunnyNumber(123, 2));   // -1
    return 0;
}