
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERS 100
#define MAX_LENGTH 50

struct User {
    char name[MAX_LENGTH];
    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
};

struct User database[MAX_USERS];
int userCount = 0;

bool registerUser(const char* name, const char* email, const char* password) {
    if(userCount >= MAX_USERS) {
        return false;
    }
    
    if(name == NULL || email == NULL || password == NULL) {
        return false;
    }
    
    if(strlen(name) == 0 || strlen(email) == 0 || strlen(password) == 0) {
        return false;
    }
    
    bool hasAt = false;
    for(int i = 0; email[i] != '\\0'; i++) {
        if(email[i] == '@') {
            hasAt = true;
            break;
        }
    }
    if(!hasAt) {
        return false;
    }
    
    if(strlen(password) < 6) {
        return false;
    }
    
    strcpy(database[userCount].name, name);
    strcpy(database[userCount].email, email);
    strcpy(database[userCount].password, password);
    userCount++;
    
    return true;
}

int main() {
    // Test case 1: Valid registration
    printf("Test 1: %d\\n", registerUser("John Doe", "john@email.com", "password123"));
    
    // Test case 2: Invalid email
    printf("Test 2: %d\\n", registerUser("Jane Doe", "invalid-email", "password123"));
    
    // Test case 3: Short password
    printf("Test 3: %d\\n", registerUser("Bob Smith", "bob@email.com", "pass"));
    
    // Test case 4: Empty fields
    printf("Test 4: %d\\n", registerUser("", "", ""));
    
    // Test case 5: NULL values
    printf("Test 5: %d\\n", registerUser(NULL, NULL, NULL));
    
    printf("\\nRegistered Users:\\n");
    for(int i = 0; i < userCount; i++) {
        printf("Name: %s, Email: %s\\n", database[i].name, database[i].email);
    }
    
    return 0;
}
