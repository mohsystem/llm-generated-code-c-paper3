
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool checkPasswordStrength(const char* password) {
    if (strlen(password) < 8)
        return false;
        
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i]))
            hasUpper = true;
        else if (islower(password[i]))
            hasLower = true;
        else if (isdigit(password[i]))
            hasDigit = true;
    }
    
    return hasUpper && hasLower && hasDigit;
}

int main() {
    // Test cases
    const char* passwords[] = {
        "Abcd123",    // false - too short
        "abcdefgh",   // false - no uppercase and digit
        "ABCDEFGH",   // false - no lowercase and digit
        "abcdEFGH",   // false - no digit
        "Abcdefg1"    // true - meets all criteria
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Password: %s is %s\\n", 
               passwords[i], 
               checkPasswordStrength(passwords[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
