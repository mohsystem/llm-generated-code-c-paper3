
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_RESOURCES 5
#define MAX_STRING_LENGTH 256

const char* ALLOWED_RESOURCES[MAX_RESOURCES] = {
    "document1.txt", "document2.txt", "image1.jpg", "image2.jpg", "data.csv"
};

void trim(char* str) {
    if (str == NULL) return;
    
    int start = 0;
    int end = strlen(str) - 1;
    
    while (isspace((unsigned char)str[start])) start++;
    while (end >= start && isspace((unsigned char)str[end])) end--;
    
    int i;
    for (i = 0; i <= end - start; i++) {
        str[i] = str[start + i];
    }
    str[i] = '\0';
}

bool isValidResourceFormat(const char* resourceName) {
    if (resourceName == NULL || strlen(resourceName) == 0) {
        return false;
    }
    
    for (int i = 0; resourceName[i] != '\0'; i++) {
        char c = resourceName[i];
        if (!isalnum(c) && c != '.' && c != '_' && c != '-') {
            return false;
        }
    }
    return true;
}
bool containsPathTraversal(const char* resourceName) {
    return strstr(resourceName, "..") != NULL ||
           strchr(resourceName, '/') != NULL ||
           strchr(resourceName, '\\') != NULL;
}

bool isResourceAllowed(const char* resourceName) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (strcmp(resourceName, ALLOWED_RESOURCES[i]) == 0) {
            return true;
        }
    }
    return false;
}

void accessResource(const char* username, const char* resourceName, char* result) {
    char usernameCopy[MAX_STRING_LENGTH];
    char resourceCopy[MAX_STRING_LENGTH];

    // Copy and validate username
    if (username == NULL || strlen(username) == 0) {
        strcpy(result, "Error: Invalid username");
        return;
    }
    strncpy(usernameCopy, username, MAX_STRING_LENGTH - 1);
    usernameCopy[MAX_STRING_LENGTH - 1] = '\0';
    trim(usernameCopy);

    if (strlen(usernameCopy) == 0) {
        strcpy(result, "Error: Invalid username");
        return;
    }

    // Copy and validate resource name
    if (resourceName == NULL || strlen(resourceName) == 0) {
        strcpy(result, "Error: Invalid resource name");
        return;
    }
    strncpy(resourceCopy, resourceName, MAX_STRING_LENGTH - 1);
    resourceCopy[MAX_STRING_LENGTH - 1] = '\0';
    trim(resourceCopy);

    if (strlen(resourceCopy) == 0) {
        strcpy(result, "Error: Invalid resource name");
        return;
    }

    // Validate resource format
    if (!isValidResourceFormat(resourceCopy)) {
        strcpy(result, "Error: Invalid resource name format");
        return;
    }

    // Check for path traversal
    if (containsPathTraversal(resourceCopy)) {
        strcpy(result, "Error: Path traversal attempt detected");
        return;
    }

    // Check whitelist
    if (!isResourceAllowed(resourceCopy)) {
        strcpy(result, "Error: Access denied - resource not found or unauthorized");
        return;
    }

    // Success
    snprintf(result, MAX_STRING_LENGTH,
             "Success: User '%s' accessed resource '%s'",
             usernameCopy, resourceCopy);
}

int main() {
    char result[MAX_STRING_LENGTH];

    printf("=== Resource Access Control System ===\n\n");

    // Test case 1: Valid access
    printf("Test 1 - Valid access:\n");
    accessResource("john_doe", "document1.txt", result);
    printf("%s\n\n", result);

    // Test case 2: Valid access to different resource
    printf("Test 2 - Valid access to image:\n");
    accessResource("jane_smith", "image1.jpg", result);
    printf("%s\n\n", result);

    // Test case 3: Attempt to access non-existent resource
    printf("Test 3 - Non-existent resource:\n");
    accessResource("user1", "secret.txt", result);
    printf("%s\n\n", result);

    // Test case 4: Path traversal attempt
    printf("Test 4 - Path traversal attempt:\n");
    accessResource("attacker", "../../../etc/passwd", result);
    printf("%s\n\n", result);

    // Test case 5: Invalid input
    printf("Test 5 - Invalid input:\n");
    accessResource("", "document1.txt", result);
    printf("%s\n", result);
    accessResource("user2", "", result);
    printf("%s\n\n", result);

    return 0;
}
