
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MIN_LENGTH 8
#define MAX_LENGTH 20

bool resetPassword(const char* oldPassword, const char* newPassword) {
    // Validate inputs
    if (oldPassword == NULL || newPassword == NULL) {
        return false;
    }
    
    size_t len = strlen(newPassword);
    
    // Check password length
    if (len < MIN_LENGTH || len > MAX_LENGTH) {
        return false;
    }
    
    // Check password complexity
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    const char* specialChars = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    
    for (size_t i = 0; i < len; i++) {
        if (isupper((unsigned char)newPassword[i])) hasUpper = true;
        else if (islower((unsigned char)newPassword[i])) hasLower = true;
        else if (isdigit((unsigned char)newPassword[i])) hasDigit = true;
        else if (strchr(specialChars, newPassword[i]) != NULL) hasSpecial = true;
    }
    
    if (!(hasUpper && hasLower && hasDigit && hasSpecial)) {
        return false;
    }
    
    // Check if new password is same as old
    if (strcmp(newPassword, oldPassword) == 0) {
        return false;
    }
    
    return true;
}

int main() {
    // Test cases
    printf("%d\\n", resetPassword("OldPass123!", "NewPass123!"));
    printf("%d\\n", resetPassword("OldPass123!", "weakpassword"));
    printf("%d\\n", resetPassword("OldPass123!", "Short1!"));
    printf("%d\\n", resetPassword("OldPass123!", "OldPass123!"));
    printf("%d\\n", resetPassword("OldPass123!", "StrongPass123!@"));
    return 0;
}
