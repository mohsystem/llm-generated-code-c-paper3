#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

long long largestProduct(char* digits, int span) {
    if (span < 1 || span > strlen(digits)) {
        return -1; // Invalid span
    }

    long long maxProduct = 0;
    for (int i = 0; i <= strlen(digits) - span; i++) {
        long long currentProduct = 1;
        char series[span + 1];
        strncpy(series, digits + i, span);
        series[span] = '\0';

        for (int j = 0; j < span; j++) {
            if (!isdigit(series[j])) {
                return -1; // Invalid input: non-digit character
            }
            currentProduct *= (series[j] - '0');
        }
        if (currentProduct > maxProduct) {
            maxProduct = currentProduct;
        }
    }

    return maxProduct;
}

int main() {
    char testCases[][3][10] = {
        {"63915", "3", "162"},
        {"12345", "2", "20"},
        {"99999", "3", "729"},
        {"01234", "2", "6"},
        {"10203", "3", "0"}
    };

    for (int i = 0; i < 5; i++) {
        char* digits = testCases[i][0];
        int span = atoi(testCases[i][1]);
        long long expected = atoll(testCases[i][2]);
        long long result = largestProduct(digits, span);

        printf("Input: \"%s\", Span: %d, Expected: %lld, Result: %lld, Match: %d\n", 
               digits, span, expected, result, (result == expected));

    }

    return 0;
}