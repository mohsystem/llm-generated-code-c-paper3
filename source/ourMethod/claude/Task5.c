
#include <stdio.h>
#include <stdlib.h>

int persistence(long num) {
    // Validate input
    if (num < 0) {
        fprintf(stderr, "Error: Number must be positive\\n");
        return -1;
    }
    
    int count = 0;
    
    // Continue while number has more than one digit
    while (num > 9) {
        long product = 1;
        long temp = num;
        
        // Multiply all digits
        while (temp > 0) {
            long digit = temp % 10;
            
            // Check for overflow before multiplication
            if (product > 0 && digit != 0 && 
                product > LONG_MAX / digit) {
                fprintf(stderr, "Error: Multiplication overflow\\n");
                return -1;
            }
            
            product *= digit;
            temp /= 10;
        }
        
        num = product;
        count++;
    }
    
    return count;
}

int main() {
    // Test cases
    printf("%d\\n", persistence(39));    // Should output 3
    printf("%d\\n", persistence(999));   // Should output 4
    printf("%d\\n", persistence(4));     // Should output 0
    printf("%d\\n", persistence(25));    // Should output 2
    printf("%d\\n", persistence(777));   // Should output 4
    
    return 0;
}
