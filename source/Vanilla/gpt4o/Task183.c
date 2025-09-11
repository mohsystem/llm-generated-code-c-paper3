#include <stdio.h>
#include <string.h>

int largestProduct(const char *input, int span) {
    int maxProduct = 0;
    int length = strlen(input);
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
    printf("%d\n", largestProduct("9876543210", 4)); // 3024
    printf("%d\n", largestProduct("11111", 2)); // 1
    printf("%d\n", largestProduct("54321", 3)); // 60
    return 0;
}