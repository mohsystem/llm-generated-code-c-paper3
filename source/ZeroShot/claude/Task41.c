
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1024

char* processString(const char* input) {
    if (input == NULL) {
        char* result = (char*)malloc(1);
        if (result == NULL) {
            return NULL;
        }
        result[0] = '\\0';
        return result;
    }
    
    // Allocate buffer for processed string
    char* result = (char*)malloc(MAX_LENGTH + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    size_t input_len = strlen(input);
    
    // Process only alphanumeric and space characters
    for (size_t i = 0; i < input_len && j < MAX_LENGTH; i++) {
        if (isalnum(input[i]) || isspace(input[i])) {
            result[j++] = input[i];
        }
    }
    result[j] = '\\0';
    
    // Trim leading spaces
    char* start = result;
    while (*start && isspace(*start)) {
        start++;
    }
    
    // Trim trailing spaces
    char* end = start + strlen(start) - 1;
    while (end > start && isspace(*end)) {
        *end = '\\0';
        end--;
    }
    
    // Move result to start of buffer if needed
    if (start != result) {
        memmove(result, start, strlen(start) + 1);
    }
    
    return result;
}

int main() {
    // Test cases
    const char* tests[] = {
        "Hello World!",
        "Test@123#$%",
        NULL,
        "AAAAA...", // Simulating long string
        "  Spaces  Test  "
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i] ? tests[i] : "NULL");
        char* processed = processString(tests[i]);
        if (processed) {
            printf("Processed: %s\\n\\n", processed);
            free(processed);
        } else {
            printf("Memory allocation failed\\n\\n");
        }
    }
    
    return 0;
}
