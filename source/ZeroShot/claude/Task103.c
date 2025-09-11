
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool checkPasswordStrength(const char* password) {
    if (password == NULL || strlen(password) < 8) {
        return false;
    }
    
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    
    for (int i = 0; password[i] != '\\0'; i++) {
        if (isupper(password[i])) {
            hasUpper = true;
        } else if (islower(password[i])) {
            hasLower = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
    }
    
    return hasUpper && hasLower && hasDigit;
}

int main() {
    const char* testPasswords[] = {
        "Abcd123!", // valid
        "abcd123",  // invalid - no uppercase
        "ABCD123",  // invalid - no lowercase
        "Abcdefgh", // invalid - no digit
        "Ab1"       // invalid - too short
    };
    
    int numPasswords = sizeof(testPasswords) / sizeof(testPasswords[0]);
    
    for (int i = 0; i < numPasswords; i++) {
        printf("Password: %s is %s\\n", 
               testPasswords[i], 
               checkPasswordStrength(testPasswords[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
