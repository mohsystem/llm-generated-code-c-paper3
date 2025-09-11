// Note: C does not have built-in support for sets or classes, so this is a more complex implementation.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRIVILEGES 10

typedef struct {
    char name[50];
    char *privileges[MAX_PRIVILEGES];
    int numPrivileges;
} User;

void addPrivilege(User *user, char *privilege) {
    if (user->numPrivileges < MAX_PRIVILEGES) {
        user->privileges[user->numPrivileges] = privilege;
        user->numPrivileges++;
    }
}

int hasPrivilege(User *user, char *privilege) {
    for (int i = 0; i < user->numPrivileges; i++) {
        if (strcmp(user->privileges[i], privilege) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    User user1;
    strcpy(user1.name, "User1");
    user1.numPrivileges = 0;

    char *read = malloc(sizeof(char) * 5);
    strcpy(read, "READ");
    addPrivilege(&user1, read);

    char *write = malloc(sizeof(char) * 6);
    strcpy(write, "WRITE");
    addPrivilege(&user1, write);

    printf("%d\n", hasPrivilege(&user1, "READ"));  // 1 (true)
    printf("%d\n", hasPrivilege(&user1, "DELETE"));  // 0 (false)

    free(read);
    free(write);

    return 0;
}