#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool isValidPassword(const char* password) {
    bool hasDigit = false, hasUpper = false, hasLower = false, hasSpecial = false;
    size_t length = strlen(password);

    if (length < 8) return false;

    for (size_t i = 0; i < length; ++i) {
        if (isdigit(password[i])) hasDigit = true;
        else if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else hasSpecial = true;
    }

    return hasDigit && hasUpper && hasLower && hasSpecial;
}

bool resetPassword(const char* username, const char* oldPassword, const char* newPassword, char users[][2][50], size_t userCount) {
    for (size_t i = 0; i < userCount; ++i) {
        if (strcmp(users[i][0], username) == 0) {
            if (strcmp(users[i][1], oldPassword) == 0) {
                if (isValidPassword(newPassword)) {
                    strcpy(users[i][1], newPassword);
                    return true;
                }
            }
            return false;
        }
    }
    return false;
}

int main() {
    char users[2][2][50] = {{"user1", "OldPassword123!"}, {"user2", "OldPassword456!"}};

    printf("%d\n", resetPassword("user1", "OldPassword123!", "NewPassword123!", users, 2)); // true
    printf("%d\n", resetPassword("user2", "WrongPassword!", "NewPassword456!", users, 2)); // false
    printf("%d\n", resetPassword("user1", "OldPassword123!", "weak", users, 2)); // false
    printf("%d\n", resetPassword("user3", "OldPassword789!", "StrongPass1!", users, 2)); // false
    printf("%d\n", resetPassword("user2", "OldPassword456!", "StrongPass2!", users, 2)); // true

    return 0;
}