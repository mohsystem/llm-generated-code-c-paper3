
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

char* processInput(const char* input) {
    static char result[MAX_LENGTH];
    char cleanInput[MAX_LENGTH];
    int j = 0;
    
    // Input validation
    if (input == NULL || strlen(input) == 0) {
        return "Invalid input: Input cannot be empty";
    }
    
    // Remove special characters and numbers, convert to uppercase
    for(int i = 0; input[i] != '\\0'; i++) {
        if(isalpha(input[i]) || isspace(input[i])) {
            cleanInput[j++] = toupper(input[i]);
        }
    }
    cleanInput[j] = '\\0';
    
    // Reverse the string
    int len = strlen(cleanInput);
    for(int i = 0; i < len; i++) {
        result[i] = cleanInput[len - 1 - i];
    }
    result[len] = '\\0';
    
    return result;
}

int main() {
    // Test cases
    const char* testInputs[] = {
        "Hello World!",
        "Test123@#",
        "",
        NULL,
        "SecurityCheck456!"
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", testInputs[i] ? testInputs[i] : "NULL");
        printf("Output: %s\\n\\n", processInput(testInputs[i]));
    }
    
    return 0;
}
