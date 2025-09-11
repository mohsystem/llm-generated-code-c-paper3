#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool isStrongPassword(char *password) {
    if (strlen(password) < 8) {
        return false;
    }
    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) {
            hasUppercase = true;
        } else if (islower(password[i])) {
            hasLowercase = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
    }
    return hasUppercase && hasLowercase && hasDigit;
}

int main() {
    printf("%d\n", isStrongPassword("Hello123")); // true (1)
    printf("%d\n", isStrongPassword("hello")); // false (0)
    printf("%d\n", isStrongPassword("HELLO123")); // false (0)
    printf("%d\n", isStrongPassword("helloWORLD")); // false (0)
    printf("%d\n", isStrongPassword("H3ll0")); // false (0)
    return 0;
}