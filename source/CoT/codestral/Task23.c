#include <stdio.h>
#include <math.h>

int findNb(long long m) {
    long long sum = 0;
    int n = 1;
    while (sum < m) {
        sum += (long long) pow(n, 3);
        if (sum == m) {
            return n;
        }
        n++;
    }
    return -1;
}

int main() {
    printf("%d\n", findNb(1071225)); // 45
    printf("%d\n", findNb(91716553919377)); // -1
    return 0;
}