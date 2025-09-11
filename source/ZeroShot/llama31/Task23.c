#include <stdio.h>

long long findNb(long long m) {
    long long n = 1;
    long long sum = 0;
    while (sum < m) {
        sum += n * n * n;
        if (sum == m) {
            return n;
        }
        n++;
    }
    return -1;
}

int main() {
    printf("%lld\n", findNb(1071225)); // 45
    printf("%lld\n", findNb(91716553919377LL)); // -1
    printf("%lld\n", findNb(4183059834009LL)); // -1
    printf("%lld\n", findNb(275815729916296LL)); // -1
    printf("%lld\n", findNb(0)); // -1
    return 0;
}