
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isValidAdminPassword(const char* password) {
    if(password == NULL || strlen(password) == 0) {
        return false;
    }
    
    // Check minimum length
    if(strlen(password) < 12) {
        return false;
    }
    
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    
    const char* specialChars = "!@#$%^&*()_+-=[]{};\\':\\"\\\\|,.<>/?";
    
    for(int i = 0; password[i]; i++) {
        if(isupper(password[i])) {
            hasUpper = true;
        }
        else if(islower(password[i])) {
            hasLower = true;
        }
        else if(isdigit(password[i])) {
            hasDigit = true;
        }
        else if(strchr(specialChars, password[i])) {
            hasSpecial = true;
        }
        else if(isspace(password[i])) {
            return false; // Contains whitespace
        }
    }
    
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int main() {
    // Test cases
    const char* passwords[] = {
        "admin123", // too short
        "AdminPassword", // no special char or number
        "admin@password1", // no uppercase
        "ADMIN@PASSWORD1", // no lowercase
        "Admin@Password1", // valid password
    };
    
    for(int i = 0; i < 5; i++) {
        printf("Password: %s is %s\\n", 
            passwords[i], 
            isValidAdminPassword(passwords[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
