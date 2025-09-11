#include <stdio.h>
#include <string.h>

void accessResource(const char* resourceName) {
    if (strcmp(resourceName, "Resource1") == 0) {
        printf("Accessing Resource1\n");
    } else if (strcmp(resourceName, "Resource2") == 0) {
        printf("Accessing Resource2\n");
    } else if (strcmp(resourceName, "Resource3") == 0) {
        printf("Accessing Resource3\n");
    } else {
        printf("Resource not found\n");
    }
}

int main() {
    // Test cases
    accessResource("Resource1");
    accessResource("Resource2");
    accessResource("Resource3");
    accessResource("InvalidResource");
    accessResource("Resource1");
    return 0;
}