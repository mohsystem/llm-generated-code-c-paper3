#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int convertToInt(const char *input) {
    long long result;  // Use long long to detect overflow
    char *endptr;

    errno = 0; // Reset errno before calling strtol

    result = strtol(input, &endptr, 10);

    // Error checking
    if (errno == ERANGE) {
        return -1; // Overflow/underflow
    }
    if (endptr == input || *endptr != '\0') {
        return -1; // Not a valid integer string
    }
     if (result > INT_MAX || result < INT_MIN) {
        return -1; // Integer out of range
    }

    return (int)result;
}

int main() {
    char *testCases[] = {"123", "456.78", "abc", "-900", "10000000000"};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        int result = convertToInt(testCases[i]);
        printf("Input: %s, Output: %d\n", testCases[i], result);
    }

    return 0;
}