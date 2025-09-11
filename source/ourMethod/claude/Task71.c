
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Returns 1 if string contains only digits and optional negative sign, 0 otherwise
int is_valid_integer(const char* str) {
    if(!str || !*str) return 0;
    
    // Skip leading whitespace
    while(isspace((unsigned char)*str)) str++;
    
    // Handle negative sign
    if(*str == '-') str++;
    
    // Must have at least one digit
    if(!*str) return 0;
    
    // Check remaining characters are digits
    while(*str) {
        if(!isdigit((unsigned char)*str)) return 0;
        str++;
    }
    
    return 1;
}

// Convert string to integer, returns 1 on success and stores result in out_value
// Returns 0 on failure
int convert_string_to_int(const char* input, int* out_value) {
    if(!input || !out_value) return 0;
    
    // Create copy of input for modification
    char* trimmed = strdup(input);
    if(!trimmed) return 0;
    
    // Trim leading/trailing whitespace
    char* start = trimmed;
    char* end = trimmed + strlen(trimmed) - 1;
    
    while(isspace((unsigned char)*start)) start++;
    while(end > start && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\\0';
    
    // Validate input
    if(!is_valid_integer(start)) {
        free(trimmed);
        return 0;
    }
    
    // Convert to integer
    char* endptr;
    long value = strtol(start, &endptr, 10);
    
    // Check for conversion errors
    if(*endptr != '\\0' || value > INT_MAX || value < INT_MIN) {
        free(trimmed);
        return 0;
    }
    
    *out_value = (int)value;
    free(trimmed);
    return 1;
}

int main(int argc, char* argv[]) {
    // Test cases
    const char* test_inputs[] = {
        "123",      // Valid integer
        "-456",     // Valid negative integer
        "abc",      // Invalid - contains letters
        "12.34",    // Invalid - decimal number
        ""         // Invalid - empty string
    };
    
    // Use command line arguments if provided, otherwise use test cases
    int num_inputs = argc > 1 ? argc - 1 : 5;
    const char** inputs = argc > 1 ? (const char**)&argv[1] : test_inputs;
    
    for(int i = 0; i < num_inputs; i++) {
        int value;
        printf("Input: '%s' -> Result: ", inputs[i]);
        
        if(convert_string_to_int(inputs[i], &value)) {
            printf("%d", value);
        } else {
            printf("null");
        }
        printf("\\n");
    }
    
    return 0;
}
