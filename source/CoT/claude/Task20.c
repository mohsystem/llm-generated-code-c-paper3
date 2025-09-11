
#include <stdio.h>
#include <string.h>
#include <math.h>

long long digPow(long long n, int p) {
    char numStr[20];
    sprintf(numStr, "%lld", n);
    int len = strlen(numStr);
    long long sum = 0;
    
    for(int i = 0; i < len; i++) {
        int digit = numStr[i] - '0';
        sum += pow(digit, p + i);
    }
    
    return sum % n == 0 ? sum / n : -1;
}

int main() {
    // Test cases
    printf("%lld\\n", digPow(89, 1));     // Should print 1
    printf("%lld\\n", digPow(92, 1));     // Should print -1
    printf("%lld\\n", digPow(695, 2));    // Should print 2
    printf("%lld\\n", digPow(46288, 3));  // Should print 51
    printf("%lld\\n", digPow(123, 2));    // Should print -1
    return 0;
}
