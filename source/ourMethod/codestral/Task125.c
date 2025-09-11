#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RESOURCES 3
#define MAX_RESOURCE_NAME_LENGTH 20
#define MAX_RESOURCE_DATA_LENGTH 50

typedef struct {
    char name[MAX_RESOURCE_NAME_LENGTH];
    char data[MAX_RESOURCE_DATA_LENGTH];
} Resource;

Resource resources[MAX_RESOURCES] = {
    {"resource1", "Resource 1 Data"},
    {"resource2", "Resource 2 Data"},
    {"resource3", "Resource 3 Data"}
};

void accessResource(const char* resourceName) {
    int i;
    for (i = 0; i < MAX_RESOURCES; i++) {
        if (strcmp(resources[i].name, resourceName) == 0) {
            printf("Access granted. Resource data: %s\n", resources[i].data);
            return;
        }
    }
    printf("Access denied. Resource not found.\n");
}

int main() {
    char resourceName[MAX_RESOURCE_NAME_LENGTH];
    printf("Enter the resource name: ");
    scanf("%19s", resourceName);
    accessResource(resourceName);
    return 0;
}