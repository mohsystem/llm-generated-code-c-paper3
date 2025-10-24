#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

// Rule #6: Error handling is done via return codes.
// Returns 0 on success, -1 on failure.
int divide(int numerator, int denominator, double* result) {
    if (denominator == 0) {
        fprintf(stderr, "Error: Division by zero is not allowed.\n");
        return -1;
    }
    *result = (double)numerator / denominator;
    return 0;
}

// Returns 0 on success, -1 on failure.
int parse_string_to_int(const char* s, int* value) {
    char* endptr;
    errno = 0; // Reset errno before the call

    // Rule #1 & #7: Use safe parsing. strtol is safer than atoi/sscanf.
    long num = strtol(s, &endptr, 10);

    // Check for various conversion errors
    if (endptr == s) {
        fprintf(stderr, "Error: Input '%s' is not a valid number.\n", s);
        return -1;
    }
    if (*endptr != '\0' && *endptr != '\n') {
        fprintf(stderr, "Error: Input '%s' contains non-numeric characters.\n", s);
        return -1;
    }
    if ((errno == ERANGE && (num == LONG_MAX || num == LONG_MIN)) || (num > INT_MAX || num < INT_MIN)) {
        fprintf(stderr, "Error: Input '%s' is out of the integer range.\n", s);
        return -1;
    }

    *value = (int)num;
    return 0;
}

void process_division(const char* numStr1, const char* numStr2) {
    printf("Processing inputs: \"%s\", \"%s\"\n", numStr1, numStr2);
    int numerator, denominator;
    double result;

    if (parse_string_to_int(numStr1, &numerator) != 0) {
        // Error message is printed inside parse_string_to_int
    } else if (parse_string_to_int(numStr2, &denominator) != 0) {
        // Error message is printed inside parse_string_to_int
    } else if (divide(numerator, denominator, &result) == 0) {
        printf("Result: %f\n", result);
    }
    // All error messages are printed to stderr inside the functions.

    printf("--- Operation finished ---\n");
}

int main() {
    printf("--- Running Test Cases ---\n");

    // Test Case 1: Valid input
    process_division("10", "2");

    // Test Case 2: Division by zero
    process_division("5", "0");

    // Test Case 3: Non-numeric input for numerator
    process_division("abc", "5");

    // Test Case 4: Out of range input
    process_division("3000000000", "2");

    // Test Case 5: Input with trailing characters
    process_division("123xyz", "3");
    
    return 0;
}