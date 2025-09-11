
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RESOURCES 3
#define MAX_FILENAME 20

const char ALLOWED_RESOURCES[MAX_RESOURCES][MAX_FILENAME] = {
    "file1.txt",
    "file2.txt", 
    "file3.txt"
};

bool validateAccess(const char* requestedResource) {
    if (requestedResource == NULL || strlen(requestedResource) == 0) {
        return false;
    }
    
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (strcmp(ALLOWED_RESOURCES[i], requestedResource) == 0) {
            return true;
        }
    }
    return false;
}

void accessResource(const char* resourceName, char* result, size_t resultSize) {
    if (!validateAccess(resourceName)) {
        strncpy(result, "Access denied", resultSize - 1);
        result[resultSize - 1] = '\\0';
        return;
    }
    
    snprintf(result, resultSize, "Accessing resource: %s", resourceName);
}

int main() {
    char result[100];
    
    // Test cases
    accessResource("file1.txt", result, sizeof(result)); // Valid
    printf("%s\\n", result);
    
    accessResource("file2.txt", result, sizeof(result)); // Valid
    printf("%s\\n", result);
    
    accessResource("file4.txt", result, sizeof(result)); // Invalid
    printf("%s\\n", result);
    
    accessResource("", result, sizeof(result)); // Invalid
    printf("%s\\n", result);
    
    accessResource(NULL, result, sizeof(result)); // Invalid
    printf("%s\\n", result);
    
    return 0;
}
