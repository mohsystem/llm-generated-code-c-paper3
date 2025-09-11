#include <stdio.h>
#include <string.h>

// Simplified resource management for C (no hashmap)
char* getResource(const char* resourceName) {
    if (strcmp(resourceName, "resource1") == 0) {
        return "Data for resource 1";
    } else if (strcmp(resourceName, "resource2") == 0) {
        return "Data for resource 2";
    } else if (strcmp(resourceName, "resource3") == 0) {
        return "Data for resource 3";
    } else {
        return "Resource not found.";
    }
}

int main() {
    char resourceName[50];
    printf("Enter resource name: ");
    scanf("%s", resourceName);

    char* resourceData = getResource(resourceName);
    printf("%s\n", resourceData);


    printf("%s\n", getResource("resource1"));
    printf("%s\n", getResource("resource2"));
    printf("%s\n", getResource("resource4"));
    printf("%s\n", getResource("resource3"));
    printf("%s\n", getResource("resource5"));

    return 0;
}