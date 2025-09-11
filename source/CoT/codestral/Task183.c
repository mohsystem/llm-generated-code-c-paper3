#include <stdio.h>
#include <string.h>

int largestProduct(char *input, int span) {
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
    printf("%d\n", largestProduct("63915", 3)); // Output: 162
    return 0;
}