
#include <stdio.h>

int persistence(long long num) {
    int count = 0;
    
    while (num >= 10) {
        long long product = 1;
        while (num > 0) {
            product *= num % 10;
            num /= 10;
        }
        num = product;
        count++;
    }
    return count;
}

int main() {
    printf("Test Case 1: %d\\n", persistence(39));   // Expected: 3
    printf("Test Case 2: %d\\n", persistence(999));  // Expected: 4
    printf("Test Case 3: %d\\n", persistence(4));    // Expected: 0
    printf("Test Case 4: %d\\n", persistence(25));   // Expected: 2
    printf("Test Case 5: %d\\n", persistence(777));  // Expected: 4
    return 0;
}
