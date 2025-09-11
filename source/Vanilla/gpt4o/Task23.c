#include <stdio.h>

int findNb(long long m) {
    long long sum = 0;
    int n = 0;
    while (sum < m) {
        n++;
        sum += (long long)n * n * n;
    }
    return sum == m ? n : -1;
}

int main() {
    printf("%d\n", findNb(1071225)); // Output: 45
    printf("%d\n", findNb(91716553919377LL)); // Output: -1
    printf("%d\n", findNb(4183059834009LL)); // Output: 2022
    printf("%d\n", findNb(24723578342962LL)); // Output: -1
    printf("%d\n", findNb(135440716410000LL)); // Output: 4824
    return 0;
}