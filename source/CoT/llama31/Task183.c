#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long largestProduct(const char* input, int span) {
    if (strlen(input) < span) {
        fprintf(stderr, "Span is larger than input length\n");
        exit(EXIT_FAILURE);
    }

    long long maxProduct = 0;
    for (int i = 0; i <= strlen(input) - span; i++) {
        long long product = 1;
        for (int j = 0; j < span; j++) {
            product *= input[i + j] - '0';
        }
        maxProduct = (maxProduct > product) ? maxProduct : product;
    }
    return maxProduct;
}

int main() {
    // Test cases
    printf("%lld\n", largestProduct("63915", 3)); // Expected: 162
    printf("%lld\n", largestProduct("123456", 2)); // Expected: 72
    printf("%lld\n", largestProduct("99999", 4)); // Expected: 729
    printf("%lld\n", largestProduct("123", 2)); // Expected: 6
    printf("%lld\n", largestProduct("1", 1)); // Expected: 1
    return 0;
}