
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <stdbool.h>

#define MAX_USERS 100
#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

typedef struct {
    char username[50];
    unsigned char passwordHash[HASH_SIZE];
    unsigned char salt[SALT_SIZE];
    bool isActive;
} UserCredentials;

typedef struct {
    UserCredentials users[MAX_USERS];
    int userCount;
} Task42;

void generateHash(const char* password, const unsigned char* salt, unsigned char* hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_SIZE);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

bool registerUser(Task42* auth, const char* username, const char* password) {
    if(!username || !password || strlen(password) < 8 || auth->userCount >= MAX_USERS) {
        return false;
    }
    
    for(int i = 0; i < auth->userCount; i++) {
        if(strcmp(auth->users[i].username, username) == 0) {
            return false;
        }
    }
    
    UserCredentials* newUser = &auth->users[auth->userCount];
    strncpy(newUser->username, username, sizeof(newUser->username) - 1);
    newUser->username[sizeof(newUser->username) - 1] = '\\0';
    
    if(RAND_bytes(newUser->salt, SALT_SIZE) != 1) {
        return false;
    }
    
    generateHash(password, newUser->salt, newUser->passwordHash);
    newUser->isActive = true;
    auth->userCount++;
    
    return true;
}

bool authenticate(Task42* auth, const char* username, const char* password) {
    if(!username || !password) {
        return false;
    }
    
    for(int i = 0; i < auth->userCount; i++) {
        if(strcmp(auth->users[i].username, username) == 0 && auth->users[i].isActive) {
            unsigned char hash[HASH_SIZE];
            generateHash(password, auth->users[i].salt, hash);
            return memcmp(hash, auth->users[i].passwordHash, HASH_SIZE) == 0;
        }
    }
    
    return false;
}

int main() {
    Task42 auth = {.userCount = 0};
    
    // Test case 1: Successful registration
    printf("%d\\n", registerUser(&auth, "user1", "password123"));
    
    // Test case 2: Duplicate registration
    printf("%d\\n", registerUser(&auth, "user1", "password456"));
    
    // Test case 3: Successful authentication
    printf("%d\\n", authenticate(&auth, "user1", "password123"));
    
    // Test case 4: Failed authentication - wrong password
    printf("%d\\n", authenticate(&auth, "user1", "wrongpassword"));
    
    // Test case 5: Failed authentication - non-existent user
    printf("%d\\n", authenticate(&auth, "user2", "password123"));
    
    return 0;
}
