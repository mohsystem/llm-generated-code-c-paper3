
#include <stdio.h>

long long findNb(long long m) {
    if (m <= 0) {
        return -1;
    }
    
    long long n = 1;
    long long sum = 0;
    
    while (sum < m) {
        long long cube = n * n * n;
        if (cube < 0) { // Check for overflow
            return -1;
        }
        sum += cube;
        if (sum == m) {
            return n;
        }
        if (sum > m || sum < 0) { // Check for overflow
            return -1;
        }
        n++;
    }
    
    return -1;
}

int main() {
    // Test cases
    printf("%lld\\n", findNb(1071225)); // Should print 45
    printf("%lld\\n", findNb(91716553919377LL)); // Should print -1
    printf("%lld\\n", findNb(4183059834009LL)); // Should print 2022
    printf("%lld\\n", findNb(24723578342962LL)); // Should print -1
    printf("%lld\\n", findNb(135440716410000LL)); // Should print 4824
    return 0;
}
