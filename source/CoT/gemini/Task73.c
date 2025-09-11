#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isValidAdminPassword(const char *password) {
    if (password == NULL || strlen(password) < 12) {
        return false;
    }

    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;

    for (int i = 0; password[i] != '\0'; i++) {
        char c = password[i];
        if (isupper(c)) {
            hasUppercase = true;
        } else if (islower(c)) {
            hasLowercase = true;
        } else if (isdigit(c)) {
            hasDigit = true;
        } else if (strchr("!@#$%^&*()_+=-`~[]\\;',./{}|:\"<>?", c) != NULL) {
            hasSpecialChar = true;
        }
    }

    return hasUppercase && hasLowercase && hasDigit && hasSpecialChar;
}

int main() {
    printf("%d\n", isValidAdminPassword("Short")); //false
    printf("%d\n", isValidAdminPassword("password")); //false
    printf("%d\n", isValidAdminPassword("LongButNoSpecial")); //false
    printf("%d\n", isValidAdminPassword("LongWithSpecial!")); //false
    printf("%d\n", isValidAdminPassword("LongSecurePassw0rd!")); //true
    return 0;
}