
#include <stdio.h>
#include <string.h>
#include <math.h>

long long digPow(long long n, int p) {
    char numStr[20];
    sprintf(numStr, "%lld", n);
    long long sum = 0;
    int len = strlen(numStr);
    
    for(int i = 0; i < len; i++) {
        int digit = numStr[i] - '0';
        sum += pow(digit, p + i);
    }
    
    return sum % n == 0 ? sum / n : -1;
}

int main() {
    printf("%lld\\n", digPow(89, 1));     // 1
    printf("%lld\\n", digPow(92, 1));     // -1
    printf("%lld\\n", digPow(695, 2));    // 2
    printf("%lld\\n", digPow(46288, 3));  // 51
    printf("%lld\\n", digPow(123, 1));    // -1
    return 0;
}
