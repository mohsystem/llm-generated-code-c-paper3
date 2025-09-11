
#include <stdio.h>

long long findNb(long long m) {
    long long n = 1;
    long long sum = 0;
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
    // Test cases
    printf("%lld\\n", findNb(1071225));             // Should print 45
    printf("%lld\\n", findNb(91716553919377));      // Should print -1
    printf("%lld\\n", findNb(4183059834009));       // Should print 2022
    printf("%lld\\n", findNb(24723578342962));      // Should print -1
    printf("%lld\\n", findNb(135440716410000));     // Should print 4824
    return 0;
}
