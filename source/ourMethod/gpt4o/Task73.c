#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidAdminPassword(const char* password) {
    // Password policy:
    // Minimum 8 characters, at least one uppercase letter,
    // one lowercase letter, one number, and one special character
    if (password == NULL || strlen(password) < 8) return 0;
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSpecial = 1;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int main() {
    printf("%d\n", isValidAdminPassword("Admin123!"));  // 1
    printf("%d\n", isValidAdminPassword("admin123"));   // 0
    printf("%d\n", isValidAdminPassword("ADMIN123!"));  // 0
    printf("%d\n", isValidAdminPassword("Admin!"));     // 0
    printf("%d\n", isValidAdminPassword("Admin1234"));  // 0
    return 0;
}