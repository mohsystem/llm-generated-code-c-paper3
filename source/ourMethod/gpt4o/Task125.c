#include <stdio.h>
#include <string.h>

const char* getResource(const char* user) {
    struct {
        const char* user;
        const char* resource;
    } resourceAccess[] = {
        {"user1", "Resource A"},
        {"user2", "Resource B"},
        {"user3", "Resource C"},
        {"admin", "All Resources"}
    };

    if (user == NULL || strlen(user) == 0) {
        return "Invalid user input.";
    }

    for (int i = 0; i < 4; ++i) {
        if (strcmp(user, resourceAccess[i].user) == 0) {
            return resourceAccess[i].resource;
        }
    }
    return "Access Denied";
}

int main() {
    printf("%s\n", getResource("user1"));
    printf("%s\n", getResource("user2"));
    printf("%s\n", getResource("user3"));
    printf("%s\n", getResource("admin"));
    printf("%s\n", getResource("unknown"));
    return 0;
}