#include <stdio.h>
#include <string.h>

typedef struct {
    char userId[10];
    char resource[20];
} Resource;

const Resource resources[] = {
    {"user1", "Resource 1"},
    {"user2", "Resource 2"},
    {"user3", "Resource 3"},
};

const char* accessResource(const char *userId) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(resources[i].userId, userId) == 0) {
            return resources[i].resource;
        }
    }
    return "Access Denied";
}

int main() {
    printf("%s\n", accessResource("user1")); // Should print Resource 1
    printf("%s\n", accessResource("user2")); // Should print Resource 2
    printf("%s\n", accessResource("user3")); // Should print Resource 3
    printf("%s\n", accessResource("user4")); // Should print Access Denied
    printf("%s\n", accessResource("admin")); // Should print Access Denied
    
    return 0;
}