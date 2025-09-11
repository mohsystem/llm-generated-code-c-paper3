
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <openssl/sha.h>
#include <stdlib.h>

#define MAX_USERS 100
#define MAX_USERNAME 50
#define MAX_HASH 65

typedef struct {
    char username[MAX_USERNAME];
    char passwordHash[MAX_HASH];
} User;

typedef struct {
    User users[MAX_USERS];
    int userCount;
} UserDatabase;

void hashPassword(const char* password, char* hashResult) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashResult + (i * 2), "%02x", hash[i]);
    }
    hashResult[64] = 0;
}

bool registerUser(UserDatabase* db, const char* username, const char* password) {
    if(!username || !password || strlen(username) == 0 || strlen(password) == 0) {
        return false;
    }
    
    if(db->userCount >= MAX_USERS) {
        return false;
    }
    
    for(int i = 0; i < db->userCount; i++) {
        if(strcmp(db->users[i].username, username) == 0) {
            return false;
        }
    }
    
    User* newUser = &db->users[db->userCount];
    strncpy(newUser->username, username, MAX_USERNAME - 1);
    newUser->username[MAX_USERNAME - 1] = 0;
    hashPassword(password, newUser->passwordHash);
    
    db->userCount++;
    return true;
}

bool authenticateUser(UserDatabase* db, const char* username, const char* password) {
    if(!username || !password) {
        return false;
    }
    
    char inputHash[MAX_HASH];
    hashPassword(password, inputHash);
    
    for(int i = 0; i < db->userCount; i++) {
        if(strcmp(db->users[i].username, username) == 0) {
            return strcmp(db->users[i].passwordHash, inputHash) == 0;
        }
    }
    
    return false;
}

int main() {
    UserDatabase db = {0};
    
    // Test case 1: Successful registration
    printf("%d\\n", registerUser(&db, "user1", "password123"));
    
    // Test case 2: Duplicate registration
    printf("%d\\n", registerUser(&db, "user1", "password123"));
    
    // Test case 3: Successful authentication
    printf("%d\\n", authenticateUser(&db, "user1", "password123"));
    
    // Test case 4: Failed authentication - wrong password
    printf("%d\\n", authenticateUser(&db, "user1", "wrongpassword"));
    
    // Test case 5: Failed authentication - non-existent user
    printf("%d\\n", authenticateUser(&db, "user2", "password123"));
    
    return 0;
}
