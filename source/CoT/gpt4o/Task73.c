#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isValidAdminPassword(const char* password) {
    if (strlen(password) < 8) return false;

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (size_t i = 0; i < strlen(password); i++) {
        char ch = password[i];
        if (isupper(ch)) hasUpper = true;
        else if (islower(ch)) hasLower = true;
        else if (isdigit(ch)) hasDigit = true;
        else if (strchr("!@#$%^&*()-+", ch)) hasSpecial = true;
    }
    
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int main() {
    printf("%d\n", isValidAdminPassword("Admin@123")); // 1
    printf("%d\n", isValidAdminPassword("admin123"));  // 0
    printf("%d\n", isValidAdminPassword("ADMIN123!")); // 0
    printf("%d\n", isValidAdminPassword("Admin123"));  // 0
    printf("%d\n", isValidAdminPassword("Ad@1"));      // 0
    return 0;
}