#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long largestProduct(const char* input, int span) {
    if (input == NULL || strlen(input) < span) {
        fprintf(stderr, "Input length must be at least equal to the span\n");
        exit(EXIT_FAILURE);
    }

    long long maxProduct = 0;
    for (int i = 0; i <= strlen(input) - span; i++) {
        long long product = 1;
        for (int j = 0; j < span; j++) {
            product *= input[i + j] - '0';
        }
        if (product > maxProduct) {
            maxProduct = product;
        }
    }
    return maxProduct;
}

int main() {
    const char* input = "63915";
    int span = 3;
    printf("Largest product: %lld\n", largestProduct(input, span));

    // Test cases
    printf("Largest product for '123456' with span 3: %lld\n", largestProduct("123456", 3));
    printf("Largest product for '987654' with span 4: %lld\n", largestProduct("987654", 4));
    printf("Largest product for '111111' with span 5: %lld\n", largestProduct("111111", 5));
    printf("Largest product for '12345' with span 2: %lld\n", largestProduct("12345", 2));
    printf("Largest product for '99999' with span 1: %lld\n", largestProduct("99999", 1));

    return 0;
}