
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool check_password_strength(const char* password) {
    if (password == NULL) {
        return false;
    }
    
    // Check minimum length
    size_t length = strlen(password);
    if (length < 8) {
        return false;
    }
    
    bool has_upper = false;
    bool has_lower = false;
    bool has_digit = false;
    
    // Check each character
    for (size_t i = 0; i < length; i++) {
        if (isupper((unsigned char)password[i])) {
            has_upper = true;
        } else if (islower((unsigned char)password[i])) {
            has_lower = true;
        } else if (isdigit((unsigned char)password[i])) {
            has_digit = true;
        }
    }
    
    return has_upper && has_lower && has_digit;
}

int main() {
    // Test cases
    const char* passwords[] = {
        "Password123",  // Valid
        "password",     // Invalid: no uppercase, no digit
        "12345678",    // Invalid: no letters
        "Pass",        // Invalid: too short
        "PASSword123"  // Valid
    };
    
    const int num_passwords = 5;
    
    for (int i = 0; i < num_passwords; i++) {
        printf("Password: %s is %s\\n", 
               passwords[i], 
               check_password_strength(passwords[i]) ? "valid" : "invalid");
    }
    
    return 0;
}
