
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// Function to find the missing letter in a consecutive sequence
// Security: All inputs validated, bounds checked, safe memory operations
// Returns: the missing letter, or 0 on error
char findMissingLetter(const char *letters, size_t length, char *errorMsg, size_t errorMsgSize) {
    // Initialize error message buffer to empty (security: prevent info leak)
    if (errorMsg != NULL && errorMsgSize > 0) {
        errorMsg[0] = '\0';
    }

    // Input validation: check for NULL pointer (prevents NULL dereference)
    if (letters == NULL) {
        if (errorMsg != NULL && errorMsgSize > 0) {
            snprintf(errorMsg, errorMsgSize, "NULL pointer input");
        }
        return 0;
    }

    // Input validation: check minimum size (prevents buffer underflow)
    if (length < 2) {
        if (errorMsg != NULL && errorMsgSize > 0) {
            snprintf(errorMsg, errorMsgSize, "Array must contain at least 2 elements");
        }
        return 0;
    }

    // Input validation: check maximum size to prevent excessive processing
    if (length > 26) {
        if (errorMsg != NULL && errorMsgSize > 0) {
            snprintf(errorMsg, errorMsgSize, "Array size exceeds maximum");
        }
        return 0;
    }

    // Input validation: verify first character is a letter
    char first = letters[0];
    if (!((first >= 'a' && first <= 'z') || (first >= 'A' && first <= 'Z'))) {
        if (errorMsg != NULL && errorMsgSize > 0) {
            snprintf(errorMsg, errorMsgSize, "Invalid character in input");
        }
        return 0;
    }

    // Iterate through the array to find the gap
    // Using bounds-checked iteration to prevent buffer overflow
    for (size_t i = 0; i < length - 1; i++) {
        // Bounds check: ensure we don't access beyond array bounds
        if (i >= length) {
            if (errorMsg != NULL && errorMsgSize > 0) {
                snprintf(errorMsg, errorMsgSize, "Index out of bounds");
            }
            return 0;
        }

        char current = letters[i];

        // Input validation: ensure current character is valid letter
        if (!((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z'))) {
            if (errorMsg != NULL && errorMsgSize > 0) {
                snprintf(errorMsg, errorMsgSize, "Invalid character at position");
            }
            return 0;
        }

        // Bounds check: ensure next index is valid
        if (i + 1 >= length) {
            break;
        }

        char next = letters[i + 1];

        // Input validation: ensure next character is valid letter
        if (!((next >= 'a' && next <= 'z') || (next >= 'A' && next <= 'Z'))) {
            if (errorMsg != NULL && errorMsgSize > 0) {
                snprintf(errorMsg, errorMsgSize, "Invalid character in input");
            }
            return 0;
        }

        // Input validation: ensure same case (prevent mixed case attacks)
        bool currentIsUpper = (current >= 'A' && current <= 'Z');
        bool nextIsUpper = (next >= 'A' && next <= 'Z');
        if (currentIsUpper != nextIsUpper) {
            if (errorMsg != NULL && errorMsgSize > 0) {
                snprintf(errorMsg, errorMsgSize, "Mixed case letters not allowed");
            }
            return 0;
        }

        // Check if there's a gap (missing letter)
        // Safe integer arithmetic: chars are small values, no overflow risk
        int expectedNext = (int)current + 1;
        int actualNext = (int)next;

        if (actualNext - expectedNext == 1) {
            // Found the missing letter
            return (char)expectedNext;
        } else if (actualNext - expectedNext > 1) {
            // Gap too large (multiple missing letters - invalid input)
            if (errorMsg != NULL && errorMsgSize > 0) {
                snprintf(errorMsg, errorMsgSize, "Non-consecutive sequence");
            }
            return 0;
        }
    }

    // If we reach here, no missing letter found (invalid input)
    if (errorMsg != NULL && errorMsgSize > 0) {
        snprintf(errorMsg, errorMsgSize, "No missing letter found");
    }
    return 0;
}

int main() {
    char errorMsg[100];
    char result;
    
    // Test case 1: lowercase missing 'e'
    char test1[] = {'a', 'b', 'c', 'd', 'f'};
    result = findMissingLetter(test1, 5, errorMsg, sizeof(errorMsg));
    if (result != 0) {
        printf("Test 1: %c\n", result);
    } else {
        printf("Test 1 error: %s\n", errorMsg);
    }
    
    // Test case 2: uppercase missing 'P'
    char test2[] = {'O', 'Q', 'R', 'S'};
    result = findMissingLetter(test2, 4, errorMsg, sizeof(errorMsg));
    if (result != 0) {
        printf("Test 2: %c\n", result);
    } else {
        printf("Test 2 error: %s\n", errorMsg);
    }
    
    // Test case 3: lowercase missing 'n'
    char test3[] = {'m', 'o', 'p'};
    result = findMissingLetter(test3, 3, errorMsg, sizeof(errorMsg));
    if (result != 0) {
        printf("Test 3: %c\n", result);
    } else {
        printf("Test 3 error: %s\n", errorMsg);
    }
    
    // Test case 4: uppercase missing 'B'
    char test4[] = {'A', 'C', 'D', 'E'};
    result = findMissingLetter(test4, 4, errorMsg, sizeof(errorMsg));
    if (result != 0) {
        printf("Test 4: %c\n", result);
    } else {
        printf("Test 4 error: %s\n", errorMsg);
    }
    
    // Test case 5: lowercase missing 'x'
    char test5[] = {'w', 'y', 'z'};
    result = findMissingLetter(test5, 3, errorMsg, sizeof(errorMsg));
    if (result != 0) {
        printf("Test 5: %c\n", result);
    } else {
        printf("Test 5 error: %s\n", errorMsg);
    }
    
    return 0;
}
