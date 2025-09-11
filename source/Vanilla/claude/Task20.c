
#include <stdio.h>
#include <string.h>
#include <math.h>

long long digPow(int n, int p) {
    char nStr[20];
    sprintf(nStr, "%d", n);
    int len = strlen(nStr);
    long long sum = 0;
    
    for(int i = 0; i < len; i++) {
        int digit = nStr[i] - '0';
        sum += pow(digit, p + i);
    }
    
    if(sum % n == 0) {
        return sum / n;
    }
    return -1;
}

int main() {
    printf("%lld\\n", digPow(89, 1));     // 1
    printf("%lld\\n", digPow(92, 1));     // -1
    printf("%lld\\n", digPow(695, 2));    // 2
    printf("%lld\\n", digPow(46288, 3));  // 51
    printf("%lld\\n", digPow(123, 1));    // -1
    return 0;
}
