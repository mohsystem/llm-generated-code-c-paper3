
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

struct User {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
};

struct User users[MAX_USERS];
int userCount = 0;

bool resetPassword(const char* username, const char* oldPassword, const char* newPassword) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, oldPassword) == 0) {
                if (strlen(newPassword) < 8) {
                    return false;
                }
                strcpy(users[i].password, newPassword);
                return true;
            }
            return false;
        }
    }
    return false;
}

void addUser(const char* username, const char* password) {
    if (userCount < MAX_USERS) {
        strcpy(users[userCount].username, username);
        strcpy(users[userCount].password, password);
        userCount++;
    }
}

int main() {
    // Add test users
    addUser("user1", "password123");
    addUser("user2", "abc123xyz");
    addUser("user3", "securepass");
    
    // Test case 1: Valid password reset
    printf("%d\\n", resetPassword("user1", "password123", "newpass123")); // 1
    
    // Test case 2: Wrong old password
    printf("%d\\n", resetPassword("user2", "wrongpass", "newpass456")); // 0
    
    // Test case 3: User doesn't exist
    printf("%d\\n", resetPassword("user4", "anypass", "newpass789")); // 0
    
    // Test case 4: New password too short
    printf("%d\\n", resetPassword("user3", "securepass", "short")); // 0
    
    // Test case 5: Another valid reset
    printf("%d\\n", resetPassword("user3", "securepass", "newpassword999")); // 1
    
    return 0;
}
