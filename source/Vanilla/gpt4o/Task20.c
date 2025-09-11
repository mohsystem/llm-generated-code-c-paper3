#include <stdio.h>
#include <math.h>

int findK(int n, int p) {
    char numStr[12];
    sprintf(numStr, "%d", n);
    int sum = 0;
    for (int i = 0; numStr[i] != '\0'; i++) {
        sum += pow(numStr[i] - '0', p + i);
    }
    return sum % n == 0 ? sum / n : -1;
}

int main() {
    printf("%d\n", findK(89, 1));    // 1
    printf("%d\n", findK(92, 1));    // -1
    printf("%d\n", findK(695, 2));   // 2
    printf("%d\n", findK(46288, 3)); // 51
    printf("%d\n", findK(123, 1));   // -1
    return 0;
}