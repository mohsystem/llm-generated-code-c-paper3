
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isValidPassword(const char* password) {
    if (password == NULL || strlen(password) < 8) {
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
    printf("%d\\n", isValidPassword("Admin@123"));    // 1
    printf("%d\\n", isValidPassword("password123"));  // 0
    printf("%d\\n", isValidPassword("Pass@"));        // 0
    printf("%d\\n", isValidPassword("ADMIN@123"));    // 0
    printf("%d\\n", isValidPassword("Admin123456"));  // 0
    return 0;
}
