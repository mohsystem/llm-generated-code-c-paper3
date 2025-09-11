
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int* convertToInteger(const char* input) {
    if(input == NULL || strlen(input) == 0) {
        return NULL;
    }

    // Skip leading whitespace
    while(isspace(*input)) input++;
    
    // Check if empty after trimming
    if(*input == '\\0') {
        return NULL;
    }

    // Check if first char is negative sign
    int start = 0;
    if(input[0] == '-') {
        start = 1;
    }

    // Check if all remaining chars are digits
    for(int i = start; input[i] != '\\0'; i++) {
        if(!isdigit(input[i])) {
            return NULL;
        }
    }

    // Convert to integer
    int* result = (int*)malloc(sizeof(int));
    if(result == NULL) {
        return NULL;
    }
    
    char* endptr;
    *result = (int)strtol(input, &endptr, 10);
    
    // Check if conversion was successful
    if(*endptr != '\\0') {
        free(result);
        return NULL;
    }

    return result;
}

int main() {
    // Test cases
    const char* testInputs[] = {
        "123",
        "-456",
        "abc",
        "12.34",
        ""
    };

    for(int i = 0; i < 5; i++) {
        int* result = convertToInteger(testInputs[i]);
        printf("Input: %s\\n", testInputs[i]);
        printf("Result: %s\\n\\n", result ? itoa(*result, (char*)malloc(20), 10) : "Invalid input");
        free(result);
    }

    return 0;
}
