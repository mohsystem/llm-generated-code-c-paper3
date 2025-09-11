
#include <stdio.h>
#include <string.h>
#include <limits.h>

long long digPow(long long n, int p) {
    // Input validation
    if (n <= 0 || p <= 0) {
        return -1;
    }
    
    // Convert number to string
    char numStr[32];
    snprintf(numStr, sizeof(numStr), "%lld", n);
    
    long long sum = 0;
    int currentPower = p;
    size_t len = strlen(numStr);
    
    // Calculate sum of powered digits
    for (size_t i = 0; i < len; i++) {
        int num = numStr[i] - '0';
        long long powResult = 1;
        
        // Manual power calculation to prevent overflow
        for (int j = 0; j < currentPower; j++) {
            if (powResult > LLONG_MAX / num) {
                return -1; // Prevent overflow
            }
            powResult *= num;
        }
        
        if (sum > LLONG_MAX - powResult) {
            return -1; // Prevent overflow
        }
        sum += powResult;
        currentPower++;
    }
    
    // Check if there exists a k that satisfies the equation
    if (sum % n == 0) {
        long long k = sum / n;
        if (k > 0) {
            return k;
        }
    }
    return -1;
}

int main() {
    // Test cases
    printf("%lld\\n", digPow(89, 1));     // Should print 1
    printf("%lld\\n", digPow(92, 1));     // Should print -1
    printf("%lld\\n", digPow(695, 2));    // Should print 2
    printf("%lld\\n", digPow(46288, 3));  // Should print 51
    printf("%lld\\n", digPow(0, 1));      // Should print -1
    return 0;
}
