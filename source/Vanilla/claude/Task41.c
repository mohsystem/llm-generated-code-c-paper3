
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

char* processString(char* input, char* output) {
    if (input == NULL || strlen(input) > MAX_LENGTH) {
        strcpy(output, "Invalid input");
        return output;
    }
    
    // Copy input to output to preserve original
    strncpy(output, input, MAX_LENGTH);
    output[MAX_LENGTH] = '\\0';
    
    // Trim start
    int start = 0;
    while(isspace(output[start])) start++;
    
    // Trim end
    int end = strlen(output) - 1;
    while(end > start && isspace(output[end])) end--;
    
    // Shift string to remove leading spaces
    int i;
    for(i = 0; i <= end-start; i++) {
        output[i] = tolower(output[start + i]);
    }
    output[i] = '\\0';
    
    return output;
}

int main() {
    char output[MAX_LENGTH + 1];
    
    // Test cases
    char* tests[] = {
        "Hello World",
        "   TESTING SPACES   ",
        "123!@#$%",
        "",
        "AAAAAA" // shorter test case for C
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i]);
        printf("Output: %s\\n\\n", processString(tests[i], output));
    }
    
    return 0;
}
