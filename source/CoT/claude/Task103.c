
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
    const char* passwords[] = {
        "Password123",  // valid
        "password",     // no uppercase, no digit
        "12345678",    // no letters
        "Pass123",     // too short
        "PASSword123"  // valid
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Password: %s is %s\\n", 
               passwords[i], 
               checkPasswordStrength(passwords[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
