
#include <stdio.h>
#include <string.h>
#include <ctype.h>

long findLargestProduct(const char* input, int span) {
    if (input == NULL || strlen(input) < span || span <= 0) {
        return -1;
    }
    
    long maxProduct = 0;
    for (size_t i = 0; i <= strlen(input) - span; i++) {
        long product = 1;
        int validSeries = 1;
        
        for (int j = 0; j < span; j++) {
            if (!isdigit(input[i + j])) {
                validSeries = 0;
                break;
            }
            product *= (input[i + j] - '0');
        }
        
        if (validSeries && product > maxProduct) {
            maxProduct = product;
        }
    }
    return maxProduct;
}

int main() {
    // Test cases
    printf("%ld\\n", findLargestProduct("63915", 3));    // Expected: 162
    printf("%ld\\n", findLargestProduct("12345", 2));    // Expected: 20
    printf("%ld\\n", findLargestProduct("987654", 4));   // Expected: 3024
    printf("%ld\\n", findLargestProduct("1111", 2));     // Expected: 1
    printf("%ld\\n", findLargestProduct("54321", 1));    // Expected: 5
    return 0;
}
