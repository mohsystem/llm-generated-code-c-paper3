#include <stdio.h>

long long findNb(long long m) {
    long long sum = 0;
    int n = 0;
    while (sum < m) {
        n++;
        sum += (long long)n * n * n;
    }
    return sum == m ? n : -1;
}

int main() {
    printf("%d\n", findNb(1071225)); // 45
    printf("%d\n", findNb(91716553919377)); // -1
    printf("%d\n", findNb(4183059834009)); // 2022
    printf("%d\n", findNb(24723578342962)); // -1
    printf("%d\n", findNb(135440716410000)); // 4824
    return 0;
}