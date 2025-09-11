#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int largestProduct(const char* input, int span) {
    int length = strlen(input);
    if (span > length || span <= 0) {
        fprintf(stderr, "Span must be a positive integer less than or equal to the length of the input.\n");
        exit(EXIT_FAILURE);
    }
    int maxProduct = 0;
    for (int i = 0; i <= length - span; i++) {
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
    printf("%d\n", largestProduct("63915", 3)); // 162
    printf("%d\n", largestProduct("123456789", 2)); // 72
    printf("%d\n", largestProduct("987654321", 3)); // 504
    printf("%d\n", largestProduct("11111", 4)); // 1
    printf("%d\n", largestProduct("12345", 5)); // 120
    return 0;
}