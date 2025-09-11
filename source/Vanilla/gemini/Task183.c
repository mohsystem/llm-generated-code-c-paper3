#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long largestProduct(char* digits, int span) {
    if (span < 1 || span > strlen(digits)) {
        return 0;
    }

    long long maxProduct = 0;
    for (int i = 0; i <= strlen(digits) - span; i++) {
        long long currentProduct = 1;
        for (int j = 0; j < span; j++) {
            currentProduct *= (digits[i + j] - '0');
        }
        if (currentProduct > maxProduct) {
            maxProduct = currentProduct;
        }
    }
    return maxProduct;
}

int main() {
    char testCases[][50] = {
         "63915", "1027839564", "73167176531330624919225119674426574742355349194934", "99999", "123"
    };
    int spans[] = {3, 5, 6, 3, 4};
    long long expectedOutputs[] = {162, 7560, 23520, 729, 0};
    int numTestCases = sizeof(spans)/sizeof(spans[0]);

    for (int i = 0; i < numTestCases; i++){
        long long actualOutput = largestProduct(testCases[i], spans[i]);

        if (actualOutput == expectedOutputs[i]) {
            printf("Test case passed: %s, %d -> %lld\n", testCases[i], spans[i], actualOutput);
        } else {
            printf("Test case failed: %s, %d -> %lld (expected %lld)\n", testCases[i], spans[i], actualOutput, expectedOutputs[i]);
        }
    }

    return 0;
}