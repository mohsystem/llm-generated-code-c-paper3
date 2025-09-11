
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT 1000
#define BUFFER_SIZE (MAX_INPUT + 1)

char* processString(const char* input) {
    // Check for null input
    if (input == NULL) {
        char* empty = malloc(1);
        if (empty) {
            empty[0] = '\\0';
        }
        return empty;
    }
    
    // Allocate buffer with room for null terminator
    char* result = malloc(BUFFER_SIZE);
    if (!result) {
        return NULL;
    }
    
    // Copy input safely
    strncpy(result, input, MAX_INPUT);
    result[MAX_INPUT] = '\\0';
    
    // Trim leading spaces
    char* start = result;
    while(isspace((unsigned char)*start)) start++;
    
    // Trim trailing spaces
    char* end = start + strlen(start) - 1;
    while(end > start && isspace((unsigned char)*end)) end--;
    *(end + 1) = '\\0';
    
    // Move result to start of buffer if needed
    if (start != result) {
        memmove(result, start, strlen(start) + 1);
    }
    
    return result;
}

int main() {
    // Test cases
    char* result;
    
    result = processString(NULL);
    printf("NULL input: '%s'\\n", result);
    free(result);
    
    result = processString("");
    printf("Empty string: '%s'\\n", result);
    free(result);
    
    result = processString("Hello World");
    printf("Normal case: '%s'\\n", result);
    free(result);
    
    result = processString("   Spaces   ");
    printf("Spaces case: '%s'\\n", result);
    free(result);
    
    // Create long string
    char longStr[2000];
    memset(longStr, 'A', 1999);
    longStr[1999] = '\\0';
    result = processString(longStr);
    printf("Long string length: %lu\\n", strlen(result));
    free(result);
    
    return 0;
}
