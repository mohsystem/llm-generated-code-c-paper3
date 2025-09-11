
#include <stdio.h>
#include <string.h>
#include <ctype.h>

long long findLargestProduct(const char* input, int span) {
    if (input == NULL || strlen(input) < span || span <= 0) {
        return 0;
    }
    
    long long maxProduct = 0;
    int inputLen = strlen(input);
    
    for (int i = 0; i <= inputLen - span; i++) {
        long long currentProduct = 1;
        int validSeries = 1;
        
        for (int j = 0; j < span; j++) {
            if (!isdigit(input[i + j])) {
                validSeries = 0;
                break;
            }
            currentProduct *= (input[i + j] - '0');
        }
        
        if (validSeries && currentProduct > maxProduct) {
            maxProduct = currentProduct;
        }
    }
    
    return maxProduct;
}

int main() {
    // Test cases
    printf("%lld\\n", findLargestProduct("63915", 3));    // Expected: 162
    printf("%lld\\n", findLargestProduct("12345", 2));    // Expected: 20
    printf("%lld\\n", findLargestProduct("987654", 4));   // Expected: 3024
    printf("%lld\\n", findLargestProduct("1", 1));        // Expected: 1
    printf("%lld\\n", findLargestProduct("", 1));         // Expected: 0
    return 0;
}
