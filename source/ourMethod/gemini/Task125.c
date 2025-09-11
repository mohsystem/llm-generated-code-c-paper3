#include <stdio.h>
#include <string.h>

// Define a simple structure to represent a resource
typedef struct {
    char name[50];
    char content[100];
} Resource;

// Function to retrieve a resource by name
char* getResource(const char* resourceName) {
    // Define an array of resources
    Resource resources[] = {
        {"resource1", "Content of resource 1"},
        {"resource2", "Content of resource 2"},
        {"resource3", "Content of resource 3"}
    };
    int numResources = sizeof(resources) / sizeof(resources[0]);

    if (resourceName == NULL || strlen(resourceName) == 0) {
        return "Invalid resource name.";
    }


    for (int i = 0; i < numResources; i++) {
        if (strcmp(resourceName, resources[i].name) == 0) {
            return resources[i].content;
        }
    }

    return "Resource not found.";
}

int main() {
    // Test cases
    printf("%s\n", getResource("resource1")); // Expected: Content of resource 1
    printf("%s\n", getResource("resource4")); // Expected: Resource not found.
    printf("%s\n", getResource("")); // Expected: Invalid resource name.
    printf("%s\n", getResource(NULL)); // Expected: Invalid resource name.
    printf("%s\n", getResource("resource2")); // Expected: Content of resource 2

    char resourceName[50];
    printf("Enter resource name: ");
    scanf("%s", resourceName);

    char *resourceContent = getResource(resourceName);
    printf("%s\n", resourceContent);
    
    return 0;
}