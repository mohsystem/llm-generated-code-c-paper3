
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MIN_LENGTH 8
#define MAX_LENGTH 20
#define SPECIAL_CHARS "!@#$%^&*()_+-=[]{}|;:,.<>?"
#define TEMP_PASSWORD_LENGTH 12

int isPasswordStrong(const char* password) {
    int len = strlen(password);
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    
    if (len < MIN_LENGTH || len > MAX_LENGTH) {
        return 0;
    }
    
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else if (strchr(SPECIAL_CHARS, password[i])) hasSpecial = 1;
    }
    
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

const char* resetPassword(const char* oldPassword, const char* newPassword, const char* confirmPassword) {
    // Check if new password matches confirmation
    if (strcmp(newPassword, confirmPassword) != 0) {
        return "New password and confirmation do not match";
    }
    
    // Validate password strength
    if (!isPasswordStrong(newPassword)) {
        return "Password must be 8-20 characters and contain uppercase, lowercase, numbers and special characters";
    }
    
    // Check if new password is same as old
    if (strcmp(newPassword, oldPassword) == 0) {
        return "New password must be different from old password";
    }
    
    // Password reset successful - in real system would update in database
    return "Password successfully reset";
}

void generateTempPassword(char* buffer) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" SPECIAL_CHARS;
    int charset_length = strlen(charset);
    
    srand(time(NULL));
    
    for (int i = 0; i < TEMP_PASSWORD_LENGTH; i++) {
        int index = rand() % charset_length;
        buffer[i] = charset[index];
    }
    buffer[TEMP_PASSWORD_LENGTH] = '\\0';
}

int main() {
    char temp_password[TEMP_PASSWORD_LENGTH + 1];
    
    // Test case 1: Password reset success
    printf("%s\\n", resetPassword("OldPass123!", "NewPass123@", "NewPass123@"));
    
    // Test case 2: Password confirmation mismatch
    printf("%s\\n", resetPassword("OldPass123!", "NewPass123@", "DifferentPass123@"));
    
    // Test case 3: Weak password
    printf("%s\\n", resetPassword("OldPass123!", "weak", "weak"));
    
    // Test case 4: Same as old password
    printf("%s\\n", resetPassword("OldPass123!", "OldPass123!", "OldPass123!"));
    
    // Test case 5: Generate temporary password
    generateTempPassword(temp_password);
    printf("Generated temp password: %s\\n", temp_password);
    
    return 0;
}
