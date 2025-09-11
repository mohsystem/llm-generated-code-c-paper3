
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isValidAdminPassword(const char* password) {
    if (password == NULL || strlen(password) < 12) {
        return false;
    }
    
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    const char* specialChars = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    
    for (int i = 0; password[i] != '\\0'; i++) {
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
        else if (strchr(specialChars, password[i]) != NULL) hasSpecial = true;
    }
    
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int main() {
    // Test cases
    const char* passwords[] = {
        "Admin@123456789",  // valid
        "admin123456",      // invalid - no uppercase, special char
        "Admin123456!@#",   // valid
        "Ab1!defghijkl",    // valid
        "shortpwd"          // invalid - too short
    };
    
    for (int i = 0; i < 5; i++) {
        printf("Password: %s is %s\\n", 
               passwords[i], 
               isValidAdminPassword(passwords[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
