
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Returns 1 if conversion successful, 0 if failed
// The converted value is stored in result if successful
int convertToInteger(const char* input, int* result) {
    char* endptr;
    
    // Skip whitespace
    while(isspace((unsigned char)*input)) input++;
    
    // Check if empty string
    if(*input == '\\0') return 0;
    
    // Try conversion
    long val = strtol(input, &endptr, 10);
    
    // Skip trailing whitespace
    while(isspace((unsigned char)*endptr)) endptr++;
    
    // Check if conversion was successful and complete
    if(*endptr != '\\0') return 0;
    
    // Check if value is within int range
    if(val > INT_MAX || val < INT_MIN) return 0;
    
    *result = (int)val;
    return 1;
}

int main() {
    // Test cases
    const char* tests[] = {
        "123",
        "-456",
        "0",
        "abc",
        "12.34"
    };
    int num_tests = 5;
    
    for(int i = 0; i < num_tests; i++) {
        int result;
        if(convertToInteger(tests[i], &result)) {
            printf("Input: %s -> Successfully converted to: %d\\n", tests[i], result);
        } else {
            printf("Input: %s -> Invalid integer format\\n", tests[i]);
        }
    }
    
    return 0;
}
