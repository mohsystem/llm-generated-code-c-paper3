
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct {
    int value;
    int isValid;
} IntegerResult;

IntegerResult convertToInteger(const char* input) {
    IntegerResult result = {0, 0};
    
    if (input == NULL || strlen(input) == 0) {
        return result;
    }
    
    // Check if string contains only whitespace
    int allWhitespace = 1;
    for (int i = 0; input[i] != '\\0'; i++) {
        if (!isspace((unsigned char)input[i])) {
            allWhitespace = 0;
            break;
        }
    }
    if (allWhitespace) {
        return result;
    }
    
    char* endptr;
    long val = strtol(input, &endptr, 10);
    
    // Check if conversion was successful and entire string was used
    if (*endptr == '\\0' && val >= INT_MIN && val <= INT_MAX) {
        result.value = (int)val;
        result.isValid = 1;
    }
    
    return result;
}

int main() {
    // Test cases
    const char* tests[] = {
        "123",
        "-456",
        "0",
        "abc",
        ""
    };
    
    for (int i = 0; i < 5; i++) {
        IntegerResult result = convertToInteger(tests[i]);
        printf("Input: '%s' -> Result: ", tests[i]);
        if (result.isValid) {
            printf("%d\\n", result.value);
        } else {
            printf("Invalid input\\n");
        }
    }
    
    return 0;
}
