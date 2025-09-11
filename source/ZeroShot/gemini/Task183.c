#include <stdio.h>
#include <string.h>
#include <ctype.h> // For isdigit

long long largestProduct(const char *digits, int span) {
    int len = strlen(digits);

    if (span < 1 || span > len) {
        return -1;
    }

    long long maxProduct = 0;
    for (int i = 0; i <= len - span; i++) {
        long long currentProduct = 1;
        for (int j = 0; j < span; j++) {
            if (!isdigit(digits[i + j])) {
                return -1; // Invalid input
            }
            currentProduct *= (digits[i + j] - '0');
        }
        if (currentProduct > maxProduct) {
            maxProduct = currentProduct;
        }
    }
    return maxProduct;
}

int main() {
    printf("%lld\n", largestProduct("63915", 3)); // Expected: 162
    printf("%lld\n", largestProduct("1027839564", 5)); // Expected: 2520
    printf("%lld\n", largestProduct("11111", 3)); // Expected 1
    printf("%lld\n", largestProduct("99999", 3)); // Expected 729
    printf("%lld\n", largestProduct("00000", 3)); // Expected 0
    return 0;
}