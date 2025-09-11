#include <math.h>
#include <stdio.h>

long findNb(long m) {
    long n = 1;
    long sum = 0;
    while (sum < m) {
        sum += (long) pow(n, 3);
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
    return 0;
}