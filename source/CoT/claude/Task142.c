
#include <stdio.h>
#include <stdlib.h>

int findGCD(int a, int b) {
    // Handle negative numbers by converting to positive
    a = abs(a);
    b = abs(b);
    
    // Using Euclidean algorithm to find GCD
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    // Test cases
    printf("%d\\n", findGCD(48, 36));  // Should print 12
    printf("%d\\n", findGCD(54, 24));  // Should print 6
    printf("%d\\n", findGCD(7, 13));   // Should print 1
    printf("%d\\n", findGCD(48, -36)); // Should print 12
    printf("%d\\n", findGCD(0, 5));    // Should print 5
    return 0;
}
