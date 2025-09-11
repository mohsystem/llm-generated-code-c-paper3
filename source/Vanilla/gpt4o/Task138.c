#include <stdio.h>
#include <string.h>

struct Task138 {
    char username[50];
    char role[50];
};

const char* getPrivileges(const char* role) {
    if (strcmp(role, "admin") == 0) {
        return "All Access";
    } else if (strcmp(role, "editor") == 0) {
        return "Edit Access";
    } else if (strcmp(role, "viewer") == 0) {
        return "View Access";
    } else {
        return "No Access";
    }
}

int main() {
    struct Task138 user1 = {"Alice", "admin"};
    struct Task138 user2 = {"Bob", "editor"};
    struct Task138 user3 = {"Charlie", "viewer"};
    struct Task138 user4 = {"David", "guest"};
    struct Task138 user5 = {"Eve", "admin"};

    printf("%s: %s\n", user1.username, getPrivileges(user1.role));
    printf("%s: %s\n", user2.username, getPrivileges(user2.role));
    printf("%s: %s\n", user3.username, getPrivileges(user3.role));
    printf("%s: %s\n", user4.username, getPrivileges(user4.role));
    printf("%s: %s\n", user5.username, getPrivileges(user5.role));

    return 0;
}