#include <stdio.h>
#include <string.h>

// Note: C does not have built-in hash maps, so we use a simple array for demonstration.
// In a real-world application, a more robust solution would be needed.

typedef struct {
    char name[50];
    char path[100];
} Resource;

const Resource resources[] = {
    {"resource1", "path/to/resource1"},
    {"resource2", "path/to/resource2"},
    {"resource3", "path/to/resource3"}
};

const int numResources = sizeof(resources) / sizeof(resources[0]);

char* getResourcePath(const char* resourceName) {
    for (int i = 0; i < numResources; i++) {
        if (strcmp(resourceName, resources[i].name) == 0) {
            return resources[i].path;
        }
    }
    return NULL; // Return NULL if not found
}


int main() {
    char resourceName[50];
    printf("Enter resource name: ");
    scanf("%s", resourceName); 

    char* resourcePath = getResourcePath(resourceName);

    if (resourcePath != NULL) {
        printf("Path: %s\n", resourcePath);
    } else {
        printf("Resource not found.\n");
    }

        // Test cases
    printf("%s\n", getResourcePath("resource1")); // Expected: path/to/resource1
    printf("%s\n", getResourcePath("resource2")); // Expected: path/to/resource2
    printf("%s\n", getResourcePath("resource3")); // Expected: path/to/resource3
    printf("%s\n", getResourcePath("resource4")); // Expected: (null)
    printf("%s\n", getResourcePath("resource1.txt")); // Expected: (null)

    return 0;
}