
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert_to_int(const char* str, int* result) {
    char* endptr;
    long val = strtol(str, &endptr, 10);
    
    // Check if conversion was successful
    if (*endptr != '\\0' || endptr == str) {
        return 0;  // Conversion failed
    }
    
    *result = (int)val;
    return 1;  // Conversion successful
}

int main() {
    // Test cases
    const char* test_inputs[] = {"123", "-456", "0", "abc", "12.34"};
    int num_tests = 5;
    
    for(int i = 0; i < num_tests; i++) {
        int result;
        if(convert_to_int(test_inputs[i], &result)) {
            printf("Input: %s -> Successfully converted to: %d\\n", test_inputs[i], result);
        } else {
            printf("Input: %s -> Conversion failed\\n", test_inputs[i]);
        }
    }
    
    return 0;
}
