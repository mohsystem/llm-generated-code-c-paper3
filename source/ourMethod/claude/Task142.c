
#include <stdio.h>
#include <stdlib.h>

int findGCD(int a, int b) {
    // Handle negative numbers by taking absolute values
    a = abs(a);
    b = abs(b);
    
    // Base case - when one number is 0, GCD is the other number
    if (b == 0) {
        return a;
    }
    
    // Recursive Euclidean algorithm to find GCD
    return findGCD(b, a % b);
}

int main() {
    // Test cases
    printf("GCD(48, 36) = %d\\n", findGCD(48, 36));    // Should print 12
    printf("GCD(54, 24) = %d\\n", findGCD(54, 24));    // Should print 6
    printf("GCD(7, 13) = %d\\n", findGCD(7, 13));      // Should print 1
    printf("GCD(48, 0) = %d\\n", findGCD(48, 0));      // Should print 48
    printf("GCD(-54, 24) = %d\\n", findGCD(-54, 24));  // Should print 6
    return 0;
}
