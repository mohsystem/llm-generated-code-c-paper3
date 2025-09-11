
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

bool validateInput(const char* input) {
    if(input == NULL || strlen(input) == 0) {
        return false;
    }
    
    regex_t regex;
    int ret;
    
    // Compile regex pattern
    ret = regcomp(&regex, "^[a-zA-Z0-9]\\\\{5,20\\\\}$", REG_EXTENDED);
    if(ret) {
        return false;
    }
    
    // Execute regex comparison
    ret = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

int main() {
    // Test cases
    const char* tests[] = {
        "abc123",         // valid
        "test@123",       // invalid - special char
        "ab",            // invalid - too short  
        "abcdefghijklmnopqrstuvwxyz", // invalid - too long
        "ValidInput123"   // valid
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s -> Valid: %s\\n", 
               tests[i], 
               validateInput(tests[i]) ? "true" : "false");
    }
    
    return 0;
}
