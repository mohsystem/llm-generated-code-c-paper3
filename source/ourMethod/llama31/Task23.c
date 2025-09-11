#include <stdio.h>

long long find_nb(long long m) {
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
    printf("%lld\n", find_nb(1071225)); // 45
    printf("%lld\n", find_nb(91716553919377LL)); // -1
    return 0;
}