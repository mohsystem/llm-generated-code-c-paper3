#include <stdio.h>

int findNb(long long m) {
    long long volume = 0;
    int n = 0;
    
    while (volume < m) {
        n++;
        volume += (long long)n * n * n;
    }
    
    return volume == m ? n : -1;
}

int main() {
    printf("%d\n", findNb(1071225)); // 45
    printf("%d\n", findNb(91716553919377LL)); // -1
    printf("%d\n", findNb(4183059834009LL)); // 2022
    printf("%d\n", findNb(24723578342962LL)); // -1
    printf("%d\n", findNb(135440716410000LL)); // 4824
    return 0;
}