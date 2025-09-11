#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isValidAdminPassword(const char *password) {
    if (strlen(password) < 8) return 0;
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = 1;
        if (islower(password[i])) hasLower = 1;
        if (isdigit(password[i])) hasDigit = 1;
        if (strchr("!@#$%^&*()", password[i])) hasSpecial = 1;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int main() {
    // Test cases
    printf("%d\n", isValidAdminPassword("Admin123!"));  // 1 (true)
    printf("%d\n", isValidAdminPassword("admin123"));   // 0 (false)
    printf("%d\n", isValidAdminPassword("Admin!"));     // 0 (false)
    printf("%d\n", isValidAdminPassword("12345678"));   // 0 (false)
    printf("%d\n", isValidAdminPassword("AdminUser1$"));// 1 (true)
    return 0;
}