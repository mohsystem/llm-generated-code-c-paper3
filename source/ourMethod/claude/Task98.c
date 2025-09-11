
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>

int convertToInteger(const char* input, int* result) {
    if(input == NULL || result == NULL || 
       *input == '\\0' || strspn(input, " \\t\\n\\r") == strlen(input)) {
        return 0;
    }
    
    // Skip leading whitespace
    while(isspace((unsigned char)*input)) {
        input++;
    }
    
    char* endptr;
    errno = 0;
    long val = strtol(input, &endptr, 10);
    
    // Check for conversion errors
    if(errno == ERANGE || val > INT_MAX || val < INT_MIN ||
       input == endptr || *endptr != '\\0') {
        return 0;
    }
    
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
        ""
    };
    
    int num_tests = sizeof(tests) / sizeof(tests[0]);
    
    for(int i = 0; i < num_tests; i++) {
        int result;
        int success = convertToInteger(tests[i], &result);
        
        printf("Input: \\"%s\\" -> Output: ", tests[i]);
        if(success) {
            printf("%d\\n", result);
        } else {
            printf("null\\n");
        }
    }
    
    return 0;
}
