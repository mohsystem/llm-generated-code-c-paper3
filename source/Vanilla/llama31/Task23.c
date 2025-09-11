#include <stdio.h>

int findNb(long long m) {
    long long n = 1;
    long long sum = 0;
    while (sum < m) {
        sum += n * n * n;
        if (sum == m) {
            return (int) n;
        }
        n++;
    }
    return -1;
}

int main() {
    printf("%d\n", findNb(1071225)); // 45
    printf("%d\n", findNb(91716553919377LL)); // -1
    printf("%d\n", findNb(4183059834009LL)); // -1
    printf("%d\n", findNb(135440716410000LL)); // -1
    printf("%d\n", findNb(1)); // 1
    return 0;
}