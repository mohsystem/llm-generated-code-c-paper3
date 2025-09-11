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
    for (int i = 0; password[i] != '\0'; i++) {
        char c = password[i];
        if (isupper(c)) {
            hasUpperCase = true;
        } else if (islower(c)) {
            hasLowerCase = true;
        } else if (isdigit(c)) {
            hasDigit = true;
        }
    }
    return hasUpperCase && hasLowerCase && hasDigit;
}

int main() {
    printf("%d\n", isStrongPassword("Abc12345")); // 1 (true)
    printf("%d\n", isStrongPassword("abc12345")); // 0 (false)
    printf("%d\n", isStrongPassword("ABCdefgh")); // 0 (false)
    printf("%d\n", isStrongPassword("ABC12345")); // 1 (true)
    printf("%d\n", isStrongPassword("abcdefgh")); // 0 (false)
    return 0;
}