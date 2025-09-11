#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isValidAdminPassword(const char *password) {
    if (password == NULL || strlen(password) < 10) {
        return false;
    }
    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            hasUppercase = true;
        } else if (islower(password[i])) {
            hasLowercase = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        } else if (strchr("!@#$%^&*()_+=-`~[]{}|;':\",./<>?", password[i]) != NULL) {
            hasSpecialChar = true;
        }
    }
    return hasUppercase && hasLowercase && hasDigit && hasSpecialChar;
}

int main() {
    printf("%d\n", isValidAdminPassword("Admin123!")); //false
    printf("%d\n", isValidAdminPassword("Admin123!test")); //true
    printf("%d\n", isValidAdminPassword("short")); //false
    printf("%d\n", isValidAdminPassword("NoSpecialChars123")); //false
    printf("%d\n", isValidAdminPassword("ALLUPPERCASE123!")); //false
    return 0;
}