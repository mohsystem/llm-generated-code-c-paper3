#include <stdio.h>
#include <string.h>

typedef struct {
    char username[20];
    char password[20];
} User;

typedef struct {
    User users[5];
    int size;
} Task136;

void init(Task136 *authSystem) {
    authSystem->size = 5;
    strcpy(authSystem->users[0].username, "user1");
    strcpy(authSystem->users[0].password, "password1");
    strcpy(authSystem->users[1].username, "user2");
    strcpy(authSystem->users[1].password, "password2");
    strcpy(authSystem->users[2].username, "user3");
    strcpy(authSystem->users[2].password, "password3");
    strcpy(authSystem->users[3].username, "user4");
    strcpy(authSystem->users[3].password, "password4");
    strcpy(authSystem->users[4].username, "user5");
    strcpy(authSystem->users[4].password, "password5");
}

int authenticate(Task136 *authSystem, const char *username, const char *password) {
    for (int i = 0; i < authSystem->size; i++) {
        if (strcmp(authSystem->users[i].username, username) == 0 &&
            strcmp(authSystem->users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    Task136 authSystem;
    init(&authSystem);
    printf("%d\n", authenticate(&authSystem, "user1", "password1")); // 1 (true)
    printf("%d\n", authenticate(&authSystem, "user2", "wrongpassword")); // 0 (false)
    printf("%d\n", authenticate(&authSystem, "user3", "password3")); // 1 (true)
    printf("%d\n", authenticate(&authSystem, "unknownuser", "password4")); // 0 (false)
    printf("%d\n", authenticate(&authSystem, "user5", "password5")); // 1 (true)
    return 0;
}