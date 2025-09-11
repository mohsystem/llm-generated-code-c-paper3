
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

char* process_input(const char* input, char* result) {
    if (input == NULL) {
        strcpy(result, "Error: Input is null");
        return result;
    }
    
    // Copy input to working buffer
    char buffer[MAX_LENGTH];
    strncpy(buffer, input, MAX_LENGTH-1);
    buffer[MAX_LENGTH-1] = '\\0';
    
    // Trim whitespace
    int start = 0, end = strlen(buffer) - 1;
    while (start < strlen(buffer) && isspace(buffer[start])) start++;
    while (end > start && isspace(buffer[end])) end--;
    
    if (start > end) {
        strcpy(result, "Error: Input is empty");
        return result;
    }
    
    // Copy trimmed portion
    int j = 0;
    for (int i = start; i <= end; i++) {
        if (!isalnum(buffer[i]) && !isspace(buffer[i])) {
            strcpy(result, "Error: Input contains invalid characters");
            return result;
        }
        buffer[j++] = toupper(buffer[i]);
    }
    buffer[j] = '\\0';
    
    // Reverse string
    for (int i = 0; i < j/2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[j-1-i];
        buffer[j-1-i] = temp;
    }
    
    strcpy(result, buffer);
    return result;
}

int main() {
    char result[MAX_LENGTH];
    
    // Test cases
    const char* tests[] = {
        "Hello World",
        "",
        NULL,
        "Test123",
        "Invalid@#$"
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i] ? tests[i] : "null");
        process_input(tests[i], result);
        printf("Output: %s\\n\\n", result);
    }
    
    return 0;
}
