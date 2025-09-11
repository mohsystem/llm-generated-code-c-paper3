#include <stdio.h>
#include <string.h>

#define MAX_USERS 5
#define MAX_LENGTH 50

typedef struct {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
} User;

int resetPassword(User users[], int size, const char* username, const char* oldPassword, const char* newPassword) {
    for (int i = 0; i < size; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, oldPassword) == 0) {
            strncpy(users[i].password, newPassword, MAX_LENGTH - 1);
            users[i].password[MAX_LENGTH - 1] = '\0'; // Ensuring null-termination
            return 1;
        }
    }
    return 0;
}

int main() {
    User users[MAX_USERS] = {
        {"user1", "oldPassword1"},
        {"user2", "oldPassword2"},
        {"user3", "oldPassword3"},
        {"user4", "oldPassword4"},
        {"user5", "oldPassword5"}
    };

    printf("%d\n", resetPassword(users, MAX_USERS, "user1", "oldPassword1", "newPassword1")); // 1
    printf("%d\n", resetPassword(users, MAX_USERS, "user2", "wrongPassword", "newPassword2")); // 0
    printf("%d\n", resetPassword(users, MAX_USERS, "user3", "oldPassword3", "newPassword3")); // 1
    printf("%d\n", resetPassword(users, MAX_USERS, "user4", "oldPassword4", "newPassword4")); // 1
    printf("%d\n", resetPassword(users, MAX_USERS, "user5", "oldPassword5", "newPassword5")); // 1

    return 0;
}