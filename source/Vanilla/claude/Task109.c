
#include <stdio.h>
#include <regex.h>
#include <stdbool.h>
#include <string.h>

bool validateInput(const char* input) {
    regex_t regex;
    int reti;
    bool result;
    
    // Compile regular expression
    reti = regcomp(&regex, "^[A-Za-z][A-Za-z0-9_]{3,19}$", REG_EXTENDED);
    if (reti) {
        return false;
    }
    
    // Execute regular expression
    reti = regexec(&regex, input, 0, NULL, 0);
    result = (reti == 0);
    
    // Free compiled regular expression
    regfree(&regex);
    
    return result;
}

int main() {
    // Test cases
    const char* tests[] = {
        "User123",      // valid
        "123User",      // invalid - starts with number
        "Ab",          // invalid - too short
        "User_name_1", // valid
        "Very_long_username_123" // invalid - too long
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Input: %s -> Valid: %s\\n", 
               tests[i], 
               validateInput(tests[i]) ? "true" : "false");
    }
    
    return 0;
}
