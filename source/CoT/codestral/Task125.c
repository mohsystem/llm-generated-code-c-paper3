#include <stdio.h>
#include <string.h>

char* resources[][2] = {
    {"user1", "Resource1"},
    {"user2", "Resource2"},
    {"user3", "Resource3"}
};

const int numResources = sizeof(resources) / sizeof(resources[0]);

const char* getResource(const char* user) {
    for (int i = 0; i < numResources; i++) {
        if (strcmp(user, resources[i][0]) == 0)
            return resources[i][1];
    }
    return "Access Denied";
}

int main() {
    char user[50];
    printf("Enter username: ");
    fgets(user, sizeof(user), stdin);
    user[strcspn(user, "\n")] = 0;
    const char* resource = getResource(user);
    printf("User %s has access to: %s\n", user, resource);
    return 0;
}