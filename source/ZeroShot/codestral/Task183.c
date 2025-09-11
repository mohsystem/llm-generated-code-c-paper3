#include<stdio.h>
#include<string.h>

int maxProduct(char *input, int span) {
    int maxProduct = 0;
    for (int i = 0; i <= strlen(input) - span; i++) {
        int product = 1;
        for (int j = i; j < i + span; j++) {
            product *= input[j] - '0';
        }
        if (product > maxProduct) {
            maxProduct = product;
        }
    }
    return maxProduct;
}

int main() {
    printf("%d\n", maxProduct("63915", 3)); // 162
    printf("%d\n", maxProduct("123456789", 4)); // 5040
    printf("%d\n", maxProduct("987654321", 2)); // 72
    printf("%d\n", maxProduct("111111111", 3)); // 1
    printf("%d\n", maxProduct("999999999", 5)); // 139975393
    return 0;
}