#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Function to safely process a string, preventing buffer overflow
char* processString(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    // Calculate the length of the trimmed string
    size_t len = strlen(input);
    size_t start = 0;
    size_t end = len;

    // Find the start of the non-whitespace characters
    while (start < len && isspace((unsigned char)input[start])) {
        start++;
    }

    // Find the end of the non-whitespace characters
    while (end > start && isspace((unsigned char)input[end - 1])) {
        end--;
    }
    
    size_t trimmed_len = end - start;

    // Allocate memory for the trimmed string + null terminator
    char* result = (char*)malloc(trimmed_len + 1);
    if (result == NULL) {
        return NULL; // Memory allocation failed
    }

    // Copy the trimmed string to the result
    strncpy(result, input + start, trimmed_len);
    result[trimmed_len] = '\0'; // Null-terminate

    return result;
}

int main() {
    char input[1024]; // Large enough to avoid typical buffer overflow

    fgets(input, sizeof(input), stdin);
    // Remove the newline character if present
    input[strcspn(input, "\n")] = 0;


    char* result1 = processString(input);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }


    char* result2 = processString("   leading spaces");
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char* result3 = processString("trailing spaces   ");
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    char* result4 = processString("   both spaces   ");
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }

    char* result5 = processString(NULL);
    if(result5 == NULL) {
        printf("NULL returned as expected\n");
    }
    

    return 0;
}