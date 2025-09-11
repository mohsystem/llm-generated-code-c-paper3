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
    printf("%lld\n", findNb(4183059834009L)); // Expected: 2022
    printf("%lld\n", findNb(24723578342962L)); // Expected: -1
    printf("%lld\n", findNb(135440716410000L));// Expected: 4824
    printf("%lld\n", findNb(40539911473216L)); // Expected: 3568
    printf("%lld\n", findNb(1071225)); // Expected: 45
    printf("%lld\n", findNb(91716553919377L)); // Expected: -1
    return 0;
}