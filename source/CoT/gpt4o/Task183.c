#include <stdio.h>
#include <string.h>

int largestProduct(const char* input, int span) {
    int length = strlen(input);
    if (span > length || span < 0) return 0;
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
    printf("%d\n", largestProduct("98765", 1)); // 9
    printf("%d\n", largestProduct("00000", 3)); // 0
    printf("%d\n", largestProduct("1234", 0)); // 0
    return 0;
}