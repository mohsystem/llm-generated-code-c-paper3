#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

bool isStrongPassword(const char* password) {
    size_t length = strlen(password);

    if (length < 8) {
        return false;
    }

    bool hasUpperCase = false;
    bool hasLowerCase = false;
    bool hasDigit = false;

    for (size_t i = 0; i < length; i++) {
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
    printf("%d\n", isStrongPassword("StrongPwd1"));  // 1
    printf("%d\n", isStrongPassword("weakpassword")); // 0
    printf("%d\n", isStrongPassword("WeakPwd"));      // 0
    printf("%d\n", isStrongPassword("StrongPwd"));     // 0
    printf("%d\n", isStrongPassword("Strong1"));       // 0
    return 0;
}