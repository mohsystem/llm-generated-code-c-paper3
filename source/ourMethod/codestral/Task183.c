#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int largestProduct(const char* num, int span) {
    if (num == NULL || strlen(num) < span || span <= 0) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    int maxProduct = 0;
    for (size_t i = 0; i <= strlen(num) - span; i++) {
        int product = 1;
        for (size_t j = i; j < i + span; j++) {
            product *= num[j] - '0';
        }
        if (product > maxProduct) {
            maxProduct = product;
        }
    }
    return maxProduct;
}

int main() {
    printf("%d\n", largestProduct("63915", 3));  // 162
    printf("%d\n", largestProduct("123456789", 4));  // 2520
    printf("%d\n", largestProduct("999999", 2));  // 81
    printf("%d\n", largestProduct("000000", 2));  // 0
    printf("%d\n", largestProduct("987654321", 5));  // 362880
    return 0;
}