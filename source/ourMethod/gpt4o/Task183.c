#include <stdio.h>
#include <string.h>

int largestProduct(const char *input, int span) {
    if (span <= 0 || input == NULL || strlen(input) < span) {
        return 0;
    }

    int maxProduct = 0;

    for (size_t i = 0; i <= strlen(input) - span; i++) {
        int product = 1;
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
    printf("%d\n", largestProduct("63915", 3)); // Expected output: 162
    printf("%d\n", largestProduct("123456789", 2)); // Expected output: 72
    printf("%d\n", largestProduct("999", 2)); // Expected output: 81
    printf("%d\n", largestProduct("98765", 1)); // Expected output: 9
    printf("%d\n", largestProduct("000", 2)); // Expected output: 0
    return 0;
}