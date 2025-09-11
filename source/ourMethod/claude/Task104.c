
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char* handle_input(const char* input) {
    // Handle null input
    if (input == NULL) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\\0';
        }
        return empty;
    }
    
    // Allocate fixed size buffer
    char* buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }
    
    // Safely copy with bounds checking
    size_t input_len = strlen(input);
    size_t copy_length = input_len < (BUFFER_SIZE-1) ? input_len : (BUFFER_SIZE-1);
    
    strncpy(buffer, input, copy_length);
    buffer[copy_length] = '\\0';
    
    return buffer;
}

int main() {
    // Test cases
    char* result;
    
    result = handle_input("Test string");
    if (result) {
        printf("%s\\n", result);
        free(result);
    }
    
    result = handle_input("");
    if (result) {
        printf("%s\\n", result);
        free(result);
    }
    
    result = handle_input(NULL);
    if (result) {
        printf("%s\\n", result);
        free(result);
    }
    
    char long_str[52000] = "A very long string that exceeds buffer size...";
    for(int i = 0; i < 49; i++) {
        strcat(long_str, "A very long string that exceeds buffer size...");
    }
    result = handle_input(long_str);
    if (result) {
        printf("%s\\n", result);
        free(result);
    }
    
    result = handle_input("Special chars: !@#$%^&*()");
    if (result) {
        printf("%s\\n", result);
        free(result);
    }
    
    return 0;
}
