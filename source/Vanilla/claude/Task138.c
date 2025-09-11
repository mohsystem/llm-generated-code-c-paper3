
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char name[50];
    bool read;
    bool write;
    bool execute;
} Permission;

typedef struct {
    char username[50];
    Permission* permission;
} User;

Permission* createPermission(const char* name) {
    Permission* perm = (Permission*)malloc(sizeof(Permission));
    strcpy(perm->name, name);
    perm->read = false;
    perm->write = false;
    perm->execute = false;
    return perm;
}

User* createUser(const char* username) {
    User* user = (User*)malloc(sizeof(User));
    strcpy(user->username, username);
    user->permission = createPermission(username);
    return user;
}

void managePermission(User* user, bool read, bool write, bool execute) {
    user->permission->read = read;
    user->permission->write = write;
    user->permission->execute = execute;
}

void printUserPermissions(User* user) {
    printf("User: %s\\n", user->username);
    printf("Read: %d\\n", user->permission->read);
    printf("Write: %d\\n", user->permission->write);
    printf("Execute: %d\\n\\n", user->permission->execute);
}

void freeUser(User* user) {
    free(user->permission);
    free(user);
}

int main() {
    // Test cases
    User* user1 = createUser("admin");
    managePermission(user1, true, true, true);
    printUserPermissions(user1);
    
    User* user2 = createUser("guest");
    managePermission(user2, true, false, false);
    printUserPermissions(user2);
    
    User* user3 = createUser("developer");
    managePermission(user3, true, true, false);
    printUserPermissions(user3);
    
    User* user4 = createUser("viewer");
    managePermission(user4, true, false, false);
    printUserPermissions(user4);
    
    User* user5 = createUser("root");
    managePermission(user5, true, true, true);
    printUserPermissions(user5);
    
    // Free memory
    freeUser(user1);
    freeUser(user2);
    freeUser(user3);
    freeUser(user4);
    freeUser(user5);
    
    return 0;
}
