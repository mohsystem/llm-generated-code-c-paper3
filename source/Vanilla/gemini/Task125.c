#include <stdio.h>
#include <string.h>

char* accessResource(char* resourceName) {
    // Replace with actual resource access logic
    if (strcmp(resourceName, "resource1") == 0) {
        return "Accessing resource 1";
    } else if (strcmp(resourceName, "resource2") == 0) {
        return "Accessing resource 2";
    } else if (strcmp(resourceName, "resource3") == 0) {
        return "Accessing resource 3";
    } else {
        return "Resource not found";
    }
}

int main() {
    printf("%s\n", accessResource("resource1"));
    printf("%s\n", accessResource("resource2"));
    printf("%s\n", accessResource("resource3"));
    printf("%s\n", accessResource("resource4"));
    printf("%s\n", accessResource("resource5"));
    return 0;
}