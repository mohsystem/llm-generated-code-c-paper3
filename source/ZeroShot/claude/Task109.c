
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int validateInput(const char* input) {
    int len = strlen(input);
    
    // Check length between 5-50 chars
    if(len < 5 || len > 50) {
        return 0;
    }
    
    // Check each character is valid
    for(int i = 0; i < len; i++) {
        if(!isalnum(input[i]) && 
           input[i] != ' ' && 
           input[i] != '.' && 
           input[i] != ',' && 
           input[i] != '!' && 
           input[i] != '?' && 
           input[i] != '-') {
            return 0;
        }
    }
    return 1;
}

int main() {
    // Test cases
    const char* tests[] = {
        "Hello World!", // valid
        "Test123", // valid 
        "This is a valid input with some punctuation!", // valid
        "ab", // invalid - too short
        "This input contains invalid chars like $ and @ which are not allowed!" // invalid chars
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s\\n", tests[i]);
        printf("Valid: %s\\n\\n", validateInput(tests[i]) ? "true" : "false");
    }
    
    return 0;
}
