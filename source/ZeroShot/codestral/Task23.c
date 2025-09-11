#include <stdio.h>

long findNb(long m) {
    long n = 1;
    long sum = 0;
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
    printf("%ld\n", findNb(1071225)); // 45
    printf("%ld\n", findNb(91716553919377)); // -1
    printf("%ld\n", findNb(247235783122)); // 43
    printf("%ld\n", findNb(135440716410000)); // 48
    printf("%ld\n", findNb(4183059834009)); // 20
    return 0;
}