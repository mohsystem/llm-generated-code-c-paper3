
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

int* convertStringToInt(const char* input) {
    if (input == NULL || strlen(input) == 0) {
        return NULL;
    }
    
    // Skip leading whitespace
    while (isspace((unsigned char)*input)) {
        input++;
    }
    
    // Check if string is empty after trimming
    if (*input == '\\0') {
        return NULL;
    }
    
    char* endptr;
    errno = 0;
    long value = strtol(input, &endptr, 10);
    
    // Check for conversion errors
    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        return NULL;
    }
    
    // Check if the entire string was converted
    if (*endptr != '\\0') {
        return NULL;
    }
    
    int* result = (int*)malloc(sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    *result = (int)value;
    return result;
}

int main(int argc, char* argv[]) {
    // Test cases
    const char* testInputs[] = {"123", "-456", "abc", "12.34", ""};
    int numTests = 5;
    
    for (int i = 0; i < numTests; i++) {
        int* result = convertStringToInt(testInputs[i]);
        if (result != NULL) {
            printf("Input: %s -> Converted to: %d\\n", testInputs[i], *result);
            free(result);
        } else {
            printf("Input: %s -> Invalid integer\\n", testInputs[i]);
        }
    }
    
    // Command line argument check
    if (argc > 1) {
        int* result = convertStringToInt(argv[1]);
        if (result != NULL) {
            printf("Command line input: %s -> Converted to: %d\\n", argv[1], *result);
            free(result);
        } else {
            printf("Command line input: %s -> Invalid integer\\n", argv[1]);
        }
    }
    
    return 0;
}
