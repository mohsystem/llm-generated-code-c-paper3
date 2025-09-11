#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char username[50];
    char password[50];
} User;

int isValidPassword(const char* password) {
    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasSpecial = 0;
    if (strlen(password) < 8) return 0;
    for (int i = 0; password[i] != '\0'; i++) {
        if (isupper(password[i])) hasUpper = 1;
        else if (islower(password[i])) hasLower = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else if (strchr("!@#$%^&*()_+", password[i])) hasSpecial = 1;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

int resetPassword(User users[], int userCount, const char* username, const char* oldPassword, const char* newPassword) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, oldPassword) == 0) {
            if (isValidPassword(newPassword)) {
                strcpy(users[i].password, newPassword);
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    User users[] = {{"user1", "Password123!"}, {"user2", "Secret123!"}};
    int userCount = 2;

    printf("%d\n", resetPassword(users, userCount, "user1", "Password123!", "NewPass123!")); // 1
    printf("%d\n", resetPassword(users, userCount, "user1", "WrongPass", "NewPass123!"));   // 0
    printf("%d\n", resetPassword(users, userCount, "user2", "Secret123!", "short1!"));      // 0
    printf("%d\n", resetPassword(users, userCount, "user2", "Secret123!", "ValidPass123!"));// 1
    printf("%d\n", resetPassword(users, userCount, "user3", "SomePass", "NewPass123!"));    // 0

    return 0;
}