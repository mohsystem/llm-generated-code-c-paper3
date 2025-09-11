
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LENGTH 1024

char* processString(const char* input) {
    if (input == NULL) {
        char* result = (char*)malloc(1);
        if (result != NULL) {
            result[0] = '\\0';
        }
        return result;
    }
    
    // Allocate memory for processed string
    char* processed = (char*)malloc(MAX_LENGTH + 1);
    if (processed == NULL) {
        return NULL;
    }
    
    // Copy input with length limitation
    size_t inputLen = strlen(input);
    size_t copyLen = inputLen < MAX_LENGTH ? inputLen : MAX_LENGTH;
    strncpy(processed, input, copyLen);
    processed[copyLen] = '\\0';
    
    // Remove non-printable characters
    size_t write = 0;
    for (size_t read = 0; read < copyLen; read++) {
        if (processed[read] >= 32 && processed[read] <= 126) {
            processed[write++] = processed[read];
        }
    }
    processed[write] = '\\0';
    
    // Reverse the string
    size_t len = strlen(processed);
    for (size_t i = 0; i < len / 2; i++) {
        char temp = processed[i];
        processed[i] = processed[len - 1 - i];
        processed[len - 1 - i] = temp;
    }
    
    return processed;
}

int main() {
    // Test cases
    const char* tests[] = {
        "Hello World!",
        "Test123@#$",
        "", // Empty string
        NULL, // NULL input
        "AAAAA..." // Long string (truncated in output)
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i] ? tests[i] : "NULL");
        char* result = processString(tests[i]);
        if (result != NULL) {
            printf("Output: %s\\n\\n", result);
            free(result);
        } else {
            printf("Memory allocation failed\\n\\n");
        }
    }
    
    return 0;
}
