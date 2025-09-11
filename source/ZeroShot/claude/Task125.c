
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_authorized(const char* username, const char* role, const char* resource) {
    // Validate input
    if (!username || !role || !resource || 
        strlen(username) == 0 || strlen(role) == 0 || strlen(resource) == 0) {
        return false;
    }
    
    // Basic authorization logic
    if (strcmp(role, "admin") == 0) {
        return true;
    } else if (strcmp(role, "user") == 0) {
        return strcmp(resource, "public") == 0 || strcmp(resource, "user_data") == 0;
    } else if (strcmp(role, "guest") == 0) {
        return strcmp(resource, "public") == 0;
    }
    return false;
}

void access_resource(const char* username, const char* role, const char* resource, char* result) {
    if (is_authorized(username, role, resource)) {
        sprintf(result, "Access granted to %s for user %s", resource, username);
    } else {
        strcpy(result, "Access denied");
    }
}

int main() {
    char result[100];
    
    // Test cases
    access_resource("admin1", "admin", "confidential", result);
    printf("%s\\n", result);
    
    access_resource("user1", "user", "public", result);
    printf("%s\\n", result);
    
    access_resource("user2", "user", "admin_panel", result);
    printf("%s\\n", result);
    
    access_resource("guest1", "guest", "public", result);
    printf("%s\\n", result);
    
    access_resource("guest2", "guest", "user_data", result);
    printf("%s\\n", result);
    
    return 0;
}
