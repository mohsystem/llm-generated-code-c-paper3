#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isStrongPassword(const char* password) {
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
    printf("%d\n", isStrongPassword("Test1")); // false
    printf("%d\n", isStrongPassword("TestTest1")); // true
    printf("%d\n", isStrongPassword("TestTest")); // false
    printf("%d\n", isStrongPassword("testtest1")); // false
    printf("%d\n", isStrongPassword("TESTTEST1")); // false
    return 0;
}