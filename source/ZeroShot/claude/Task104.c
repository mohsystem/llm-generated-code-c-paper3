
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* handleInput(const char* input, size_t bufferSize) {
    if (input == NULL) {
        char* empty = malloc(1);
        if (empty != NULL) {
            empty[0] = '\\0';
        }
        return empty;
    }
    
    // Allocate fixed size buffer
    char* buffer = (char*)malloc(bufferSize + 1);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Copy input safely into buffer
    size_t inputLen = strlen(input);
    size_t length = inputLen < bufferSize ? inputLen : bufferSize;
    
    strncpy(buffer, input, length);
    buffer[length] = '\\0';
    
    return buffer;
}

int main() {
    // Test cases
    char* result;
    
    result = handleInput("Hello", 10);
    if (result) {
        printf("%s\\n", result);
        free(result);
    }
    
    result = handleInput("ThisIsALongString", 8);
    if (result) {
        printf("%s\\n", result);
        free(result);
    }
    
    result = handleInput("", 5);
    if (result) {
        printf("%s\\n", result);
        free(result);
    }
    
    result = handleInput(NULL, 5);
    if (result) {
        printf("%s\\n", result);
        free(result);
    }
    
    result = handleInput("Test", 3);
    if (result) {
        printf("%s\\n", result);
        free(result);
    }
    
    return 0;
}
