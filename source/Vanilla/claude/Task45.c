
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RESULT_LENGTH 100

void processInput(const char* input, char* result) {
    if (input == NULL || strlen(input) == 0) {
        strcpy(result, "Error: Input cannot be empty");
        return;
    }
    
    // Check if input is a valid number
    int i = 0;
    if (input[0] == '-') i = 1;
    
    for (; input[i] != '\\0'; i++) {
        if (!isdigit(input[i])) {
            strcpy(result, "Error: Input must be a valid number");
            return;
        }
    }
    
    // Convert to integer
    int num = atoi(input);
    
    if (num < 0) {
        strcpy(result, "Error: Number cannot be negative");
        return;
    }
    
    // Perform some operations
    int calculated = num * 2;
    sprintf(result, "Success: %d", calculated);
}

int main() {
    // Test cases
    const char* tests[] = {
        "123",      // Valid number
        "-5",       // Negative number
        "abc",      // Invalid number
        "",         // Empty input
        NULL        // Null input
    };
    
    char result[MAX_RESULT_LENGTH];
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i] ? tests[i] : "null");
        processInput(tests[i], result);
        printf("Output: %s\\n\\n", result);
    }
    
    return 0;
}
