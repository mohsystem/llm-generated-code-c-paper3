#include <stdio.h>

long long findNb(long long m) {
    long long n = 0;
    long long totalVolume = 0;
    while (totalVolume < m) {
        n++;
        totalVolume += n * n * n;
    }
    return totalVolume == m ? n : -1;
}

int main() {
    printf("%lld\n", findNb(1071225)); // 45
    printf("%lld\n", findNb(91716553919377)); // -1
    printf("%lld\n", findNb(4183059834009)); // 2022
    printf("%lld\n", findNb(24723578342962)); // -1
    printf("%lld\n", findNb(135440716410000)); // 4824

    return 0;
}