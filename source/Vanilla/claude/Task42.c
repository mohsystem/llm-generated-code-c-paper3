
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <stdbool.h>

#define MAX_USERS 100
#define USERNAME_LENGTH 50
#define HASH_LENGTH 65  // SHA256 hex string length + null terminator

struct User {
    char username[USERNAME_LENGTH];
    char passwordHash[HASH_LENGTH];
    bool isActive;
};

struct User users[MAX_USERS];
int userCount = 0;

void hashPassword(const char* password, char* hashResult) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashResult + (i * 2), "%02x", hash[i]);
    }
    hashResult[64] = '\\0';
}

bool registerUser(const char* username, const char* password) {
    if(userCount >= MAX_USERS) {
        return false;
    }
    
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0) {
            return false;
        }
    }
    
    strcpy(users[userCount].username, username);
    hashPassword(password, users[userCount].passwordHash);
    users[userCount].isActive = true;
    userCount++;
    return true;
}

bool authenticateUser(const char* username, const char* password) {
    char hashedPassword[HASH_LENGTH];
    hashPassword(password, hashedPassword);
    
    for(int i = 0; i < userCount; i++) {
        if(strcmp(users[i].username, username) == 0) {
            return strcmp(users[i].passwordHash, hashedPassword) == 0;
        }
    }
    return false;
}

int main() {
    // Test Case 1: Register new user
    printf("%d\\n", registerUser("user1", "pass123"));
    
    // Test Case 2: Register duplicate user
    printf("%d\\n", registerUser("user1", "pass456"));
    
    // Test Case 3: Authenticate with correct credentials
    printf("%d\\n", authenticateUser("user1", "pass123"));
    
    // Test Case 4: Authenticate with wrong password
    printf("%d\\n", authenticateUser("user1", "wrongpass"));
    
    // Test Case 5: Authenticate non-existent user
    printf("%d\\n", authenticateUser("user2", "pass123"));
    
    return 0;
}
