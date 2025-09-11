
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatenateStrings(const char** inputs, size_t count) {
    // Input validation
    if (inputs == NULL || count == 0) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\\0';
        }
        return empty;
    }
    
    // Calculate total length needed
    size_t totalLen = 1; // For null terminator
    for (size_t i = 0; i < count; i++) {
        if (inputs[i] != NULL) {
            totalLen += strlen(inputs[i]);
        }
    }
    
    // Allocate memory for result
    char* result = (char*)malloc(totalLen);
    if (result == NULL) {
        return NULL;
    }
    
    // Concatenate strings
    result[0] = '\\0';
    for (size_t i = 0; i < count; i++) {
        if (inputs[i] != NULL) {
            strcat(result, inputs[i]);
        }
    }
    
    return result;
}

int main() {
    // Test cases
    const char* test1[] = {"Hello", " ", "World"};
    char* result1 = concatenateStrings(test1, 3);
    printf("Test 1: %s\\n", result1);
    free(result1);
    
    const char* test2[] = {"Java", "Script"};
    char* result2 = concatenateStrings(test2, 2);
    printf("Test 2: %s\\n", result2);
    free(result2);
    
    const char* test3[] = {NULL, "Test"};
    char* result3 = concatenateStrings(test3, 2);
    printf("Test 3: %s\\n", result3);
    free(result3);
    
    char* result4 = concatenateStrings(NULL, 0);
    printf("Test 4: %s\\n", result4);
    free(result4);
    
    const char* test5[] = {};
    char* result5 = concatenateStrings(test5, 0);
    printf("Test 5: %s\\n", result5);
    free(result5);
    
    return 0;
}
