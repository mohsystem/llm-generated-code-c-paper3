#include <stdio.h>
#include <string.h>

long long largestProduct(const char* digits, int span) {
    if (strlen(digits) < span) {
        return 0;
    }
    long long maxProduct = 0;
    for (int i = 0; i <= strlen(digits) - span; i++) {
        long long product = 1;
        for (int j = i; j < i + span; j++) {
            product *= digits[j] - '0';
        }
        if (product > maxProduct) {
            maxProduct = product;
        }
    }
    return maxProduct;
}

int main() {
    printf("%lld\n", largestProduct("63915", 3)); // Expected: 162
    printf("%lld\n", largestProduct("12233445566778899", 4)); // Expected: 504
    printf("%lld\n", largestProduct("123456789", 3)); // Expected: 216
    printf("%lld\n", largestProduct("999999999", 3)); // Expected: 729
    printf("%lld\n", largestProduct("10001", 3)); // Expected: 0
    return 0;
}