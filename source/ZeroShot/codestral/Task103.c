#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool isStrongPassword(const char* password) {
    if (strlen(password) < 8) {
        return false;
    }
    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasDigit = false;
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) {
            hasUpperCase = true;
        } else if (islower(password[i])) {
            hasLowerCase = true;
        } else if (isdigit(password[i])) {
            hasDigit = true;
        }
    }
    return hasUpperCase && hasLowerCase && hasDigit;
}

int main() {
    printf("%d\n", isStrongPassword("Abc12345")); // 1 (true)
    printf("%d\n", isStrongPassword("abc12345")); // 0 (false)
    printf("%d\n", isStrongPassword("ABC12345")); // 0 (false)
    printf("%d\n", isStrongPassword("Abcdefgh")); // 0 (false)
    printf("%d\n", isStrongPassword("Abcdefgh1")); // 1 (true)
    return 0;
}