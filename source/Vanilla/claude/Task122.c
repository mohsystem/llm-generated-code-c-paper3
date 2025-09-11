
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct Task122 {
    struct User users[MAX_USERS];
    int userCount;
};

void initializePasswordManager(struct Task122* manager) {
    manager->userCount = 0;
}

bool signUp(struct Task122* manager, const char* username, const char* password) {
    // Check if username already exists
    for(int i = 0; i < manager->userCount; i++) {
        if(strcmp(manager->users[i].username, username) == 0) {
            return false;
        }
    }
    
    // Check if we have space for new user
    if(manager->userCount >= MAX_USERS) {
        return false;
    }
    
    // Add new user
    strncpy(manager->users[manager->userCount].username, username, MAX_USERNAME_LENGTH - 1);
    strncpy(manager->users[manager->userCount].password, password, MAX_PASSWORD_LENGTH - 1);
    manager->users[manager->userCount].username[MAX_USERNAME_LENGTH - 1] = '\\0';
    manager->users[manager->userCount].password[MAX_PASSWORD_LENGTH - 1] = '\\0';
    manager->userCount++;
    
    return true;
}

int main() {
    struct Task122 passwordManager;
    initializePasswordManager(&passwordManager);
    
    // Test Case 1: New user signup
    printf("Test 1: %s\\n", signUp(&passwordManager, "user1", "pass123") ? "true" : "false");
    
    // Test Case 2: Duplicate username
    printf("Test 2: %s\\n", signUp(&passwordManager, "user1", "differentpass") ? "true" : "false");
    
    // Test Case 3: Another new user
    printf("Test 3: %s\\n", signUp(&passwordManager, "user2", "password456") ? "true" : "false");
    
    // Test Case 4: Empty username
    printf("Test 4: %s\\n", signUp(&passwordManager, "", "pass123") ? "true" : "false");
    
    // Test Case 5: Empty password
    printf("Test 5: %s\\n", signUp(&passwordManager, "user3", "") ? "true" : "false");
    
    return 0;
}
