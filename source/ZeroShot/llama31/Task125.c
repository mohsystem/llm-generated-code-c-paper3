#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getResource(const char* resourceId, char** resources, int size) {
    int index;
    if (sscanf(resourceId + 1, "%d", &index) != 1 || index < 1 || index > size) {
        return "Resource not found";
    }
    return resources[index - 1];
}

int main() {
    char* resources[] = {"Resource 1", "Resource 2", "Resource 3", "Resource 4", "Resource 5"};
    const char* resourceIds[] = {"R1", "R2", "R3", "R4", "R5"};

    // Test cases
    for (int i = 0; i < 5; i++) {
        printf("Accessing resource with ID: %s\n", resourceIds[i]);
        char* resource = getResource(resourceIds[i], resources, 5);
        printf("%s\n\n", resource);
    }

    return 0;
}