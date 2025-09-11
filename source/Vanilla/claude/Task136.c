
#include <stdio.h>
#include <string.h>

struct User {
    char username[50];
    char password[50];
};

int authenticate(const char* username, const char* password) {
    // Hardcoded credentials for demo
    struct User validUsers[] = {
        {"admin", "admin123"},
        {"user1", "pass123"},
        {"john", "doe123"},
        {"test", "test123"},
        {"demo", "demo123"}
    };
    
    int numUsers = sizeof(validUsers) / sizeof(validUsers[0]);
    
    for(int i = 0; i < numUsers; i++) {
        if(strcmp(validUsers[i].username, username) == 0 && 
           strcmp(validUsers[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    // Test cases
    printf("%d\\n", authenticate("admin", "admin123"));  // 1
    printf("%d\\n", authenticate("user1", "pass123"));   // 1
    printf("%d\\n", authenticate("john", "wrong"));      // 0
    printf("%d\\n", authenticate("invalid", "test123")); // 0
    printf("%d\\n", authenticate("demo", "demo123"));    // 1
    return 0;
}
