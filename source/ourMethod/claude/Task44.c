
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_INPUT 100

// Function to check if string contains only alphanumeric and space
bool isValidChars(const char* str) {
    while (*str) {
        if (!isalnum(*str) && !isspace(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

// Function to trim whitespace
void trim(char* str) {
    if (!str) return;
    
    // Trim leading spaces
    char* start = str;
    while (isspace(*start)) start++;
    
    if (*start == 0) {  // All spaces
        *str = 0;
        return;
    }
    
    // Trim trailing spaces
    char* end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) end--;
    
    // Shift chars to start of string if needed
    if (start > str) {
        memmove(str, start, end - start + 1);
    }
    
    // Null terminate
    *(end + 1) = 0;
}

// Main processing function
const char* processInput(const char* input) {
    static char result[MAX_INPUT + 50]; // Extra space for message
    static char workingCopy[MAX_INPUT + 1];
    
    // Check for null input
    if (input == NULL) {
        return "Invalid input: Input cannot be empty";
    }
    
    // Create working copy and trim
    strncpy(workingCopy, input, MAX_INPUT);
    workingCopy[MAX_INPUT] = '\\0';
    trim(workingCopy);
    
    // Check for empty input
    if (strlen(workingCopy) == 0) {
        return "Invalid input: Input cannot be empty";
    }
    
    // Check length
    if (strlen(input) > MAX_INPUT) {
        return "Invalid input: Input too long (max 100 chars)";
    }
    
    // Check for invalid characters
    if (!isValidChars(workingCopy)) {
        return "Invalid input: Only alphanumeric characters allowed";
    }
    
    // Process valid input - convert to upper case
    char* ptr = workingCopy;
    while (*ptr) {
        *ptr = toupper(*ptr);
        ptr++;
    }
    
    snprintf(result, sizeof(result), "Processed input: %s", workingCopy);
    return result;
}

int main() {
    // Test cases
    const char* tests[] = {
        "Hello World",
        "", // Empty input
        "Test123!@#", // Invalid chars
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", // Too long
        "C Programming"
    };
    
    for (int i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
        printf("Input: %s\\n", tests[i]);
        printf("%s\\n\\n", processInput(tests[i]));
    }
    
    // Test null input
    printf("Input: NULL\\n");
    printf("%s\\n", processInput(NULL));
    
    return 0;
}
