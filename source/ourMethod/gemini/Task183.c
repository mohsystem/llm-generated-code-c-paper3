#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long largestProduct(const char *digits, int span) {
    if (span < 0 || span > strlen(digits)) {
         fprintf(stderr,"Span must be between 0 and the length of the digits string.\n");
         exit(1);
    }
    if (strlen(digits) == 0 || span == 0) {
        return 0;
    }

    long long largestProd = 0;
    for (int i = 0; i <= strlen(digits) - span; i++) {
        long long currentProd = 1;
        char series[span + 1];
        strncpy(series, digits + i, span);
        series[span] = '\0'; 

        for (int j = 0; j < span; j++) {
            int digit = series[j] - '0';
            if (digit < 0 || digit > 9) {
                fprintf(stderr,"Input string must contain only digits.\n");
                exit(1);

            }
            currentProd *= digit;
        }
        if (currentProd > largestProd)
        {
            largestProd = currentProd;
        }
    }

    return largestProd;
}

int main() {
    char *testDigits[] = {"12345", "63915", "99999", "10203", "00000"};
    int testSpans[] = {3, 3, 2, 1, 3};
    int numTests = sizeof(testSpans) / sizeof(testSpans[0]);


    for (int i = 0; i < numTests; i++) {
        printf("Input: \"%s\", span: %d, Largest Product: %lld\n", testDigits[i], testSpans[i], largestProduct(testDigits[i], testSpans[i]));
    }

    return 0;
}