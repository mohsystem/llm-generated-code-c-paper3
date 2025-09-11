#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long largestProduct(const char* sequence, int span) {
    if (strlen(sequence) < span) {
        fprintf(stderr, "Span is larger than the sequence length\n");
        exit(EXIT_FAILURE);
    }
    long long maxProduct = 0;
    for (int i = 0; i <= strlen(sequence) - span; ++i) {
        long long product = 1;
        for (int j = i; j < i + span; ++j) {
            product *= sequence[j] - '0';
        }
        if (product > maxProduct) {
            maxProduct = product;
        }
    }
    return maxProduct;
}

int main() {
    printf("%lld\n", largestProduct("63915", 3)); // Expected: 162
    printf("%lld\n", largestProduct("12345", 2)); // Expected: 12
    printf("%lld\n", largestProduct("98765", 4)); // Expected: 945
    printf("%lld\n", largestProduct("11111", 3)); // Expected: 1
    printf("%lld\n", largestProduct("54321", 1)); // Expected: 5
    return 0;
}