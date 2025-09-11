#include <stdio.h>
#include <math.h>

int findNb(long long m) {
    int n = 1;
    while (m > 0) {
        m -= (long long) pow(n, 3);
        if (m < 0) {
            return -1;
        }
        n++;
    }
    return m == 0 ? n - 1 : -1;
}

int main() {
    printf("%d\n", findNb(1071225)); // 45
    printf("%d\n", findNb(91716553919377LL)); // -1
    return 0;
}