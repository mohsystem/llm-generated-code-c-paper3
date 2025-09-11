
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert_to_integer(const char* input, int* result) {
    char* endptr;
    long val = strtol(input, &endptr, 10);
    
    // Check if conversion was successful
    if (endptr == input || *endptr != '\\0') {
        return 0; // Conversion failed
    }
    
    *result = (int)val;
    return 1; // Conversion successful
}

int main() {
    // Test cases
    const char* tests[] = {"123", "-456", "0", "abc", "12.34"};
    int test_count = 5;
    
    for(int i = 0; i < test_count; i++) {
        int result;
        if(convert_to_integer(tests[i], &result)) {
            printf("Successfully converted '%s' to: %d\\n", tests[i], result);
        } else {
            printf("Failed to convert: '%s'\\n", tests[i]);
        }
    }
    
    return 0;
}
