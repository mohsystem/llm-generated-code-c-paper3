
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Helper function to convert string to lowercase
void toLowerCase(char* str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

bool checkResourceAccess(const char* username, const char* resource) {
    // Input validation
    if (username == NULL || resource == NULL || 
        strlen(username) == 0 || strlen(resource) == 0) {
        return false;
    }
    
    // Create local copies for manipulation
    char user[50] = {0};
    char res[50] = {0};
    strncpy(user, username, sizeof(user) - 1);
    strncpy(res, resource, sizeof(res) - 1);
    
    // Sanitize inputs
    toLowerCase(user);
    toLowerCase(res);
    
    // Access control mapping
    if (strcmp(user, "admin") == 0) {
        return true; // Admin has access to all resources
    } else if (strcmp(user, "user") == 0) {
        // Regular user can only access public resources
        return (strcmp(res, "public_doc") == 0 || 
                strcmp(res, "shared_folder") == 0);
    } else if (strcmp(user, "guest") == 0) {
        // Guest can only access public docs
        return (strcmp(res, "public_doc") == 0);
    }
    
    return false; // Default deny access
}

int main() {
    // Test cases
    printf("%d\\n", checkResourceAccess("admin", "confidential_doc")); // 1
    printf("%d\\n", checkResourceAccess("user", "public_doc")); // 1
    printf("%d\\n", checkResourceAccess("user", "confidential_doc")); // 0
    printf("%d\\n", checkResourceAccess("guest", "public_doc")); // 1
    printf("%d\\n", checkResourceAccess("guest", "shared_folder")); // 0
    return 0;
}
