
#include <stdio.h>
#include <math.h>

long long findNb(long long m) {
    long long n = 1;
    long long sum = 0;
    while (sum < m) {
        sum += (long long)pow(n, 3);
        if (sum == m) return n;
        if (sum > m) return -1;
        n++;
    }
    return -1;
}

int main() {
    printf("%lld\\n", findNb(1071225)); // 45
    printf("%lld\\n", findNb(91716553919377)); // -1
    printf("%lld\\n", findNb(4183059834009)); // 2022
    printf("%lld\\n", findNb(24723578342962)); // -1
    printf("%lld\\n", findNb(135440716410000)); // 4824
    return 0;
}
