#include <stdio.h>

long long findNb(long long m) {
    long long n = 0;
    long long sum = 0;
    while (sum < m) {
        n++;
        sum += n * n * n;
    }
    return sum == m ? n : -1;
}

int main() {
    printf("%lld\n", findNb(1071225)); // Expected: 45
    printf("%lld\n", findNb(91716553919377)); // Expected: -1
    printf("%lld\n", findNb(4183059834009)); // Expected: 2022
    printf("%lld\n", findNb(247234522472345224)); // Expected: -1
    printf("%lld\n", findNb(1)); // Expected: 1
    return 0;
}