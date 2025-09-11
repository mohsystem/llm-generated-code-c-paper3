
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_RESOURCES 5
#define MAX_STRING_LENGTH 50

struct Resource {
    char id[MAX_STRING_LENGTH];
    char content[MAX_STRING_LENGTH];
};

struct Resource resources[MAX_RESOURCES] = {
    {"doc1", "Document 1 content"},
    {"doc2", "Document 2 content"},
    {"img1", "Image 1 content"},
    {"file1", "File 1 content"},
    {"data1", "Data 1 content"}
};

char* access_resource(const char* resource_id, const char* user_role) {
    if (resource_id == NULL || user_role == NULL) {
        return "Invalid input";
    }
    
    // Convert user_role to lowercase
    char role[MAX_STRING_LENGTH];
    strcpy(role, user_role);
    for(int i = 0; role[i]; i++) {
        role[i] = tolower(role[i]);
    }
    
    // Find resource
    int resource_index = -1;
    for(int i = 0; i < MAX_RESOURCES; i++) {
        if(strcmp(resources[i].id, resource_id) == 0) {
            resource_index = i;
            break;
        }
    }
    
    if(resource_index == -1) {
        return "Resource not found";
    }
    
    if(strcmp(role, "admin") == 0) {
        return resources[resource_index].content;
    }
    else if(strcmp(role, "user") == 0) {
        if(strncmp(resource_id, "doc", 3) == 0 || strncmp(resource_id, "img", 3) == 0) {
            return resources[resource_index].content;
        }
        return "Access denied";
    }
    else if(strcmp(role, "guest") == 0) {
        if(strncmp(resource_id, "doc", 3) == 0) {
            return resources[resource_index].content;
        }
        return "Access denied";
    }
    else {
        return "Invalid role";
    }
}

int main() {
    // Test case 1: Admin accessing document
    printf("%s\\n", access_resource("doc1", "admin"));
    
    // Test case 2: User accessing image
    printf("%s\\n", access_resource("img1", "user"));
    
    // Test case 3: Guest accessing file
    printf("%s\\n", access_resource("file1", "guest"));
    
    // Test case 4: Invalid role
    printf("%s\\n", access_resource("doc1", "invalid"));
    
    // Test case 5: Resource not found
    printf("%s\\n", access_resource("invalid", "admin"));
    
    return 0;
}
