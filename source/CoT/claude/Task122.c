
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define MAX_USERS 100
#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH

typedef struct {
    char username[50];
    unsigned char passwordHash[HASH_SIZE];
    unsigned char salt[SALT_SIZE];
    bool isUsed;
} UserCredentials;

UserCredentials userStore[MAX_USERS];
int userCount = 0;

bool signup(const char* username, const char* password) {
    if(!username || !password || strlen(username) == 0 || strlen(password) == 0) {
        return false;
    }
    
    if(userCount >= MAX_USERS) {
        return false;
    }
    
    // Check for duplicate username
    for(int i = 0; i < userCount; i++) {
        if(userStore[i].isUsed && strcmp(userStore[i].username, username) == 0) {
            return false;
        }
    }
    
    try {
        // Generate random salt
        if(RAND_bytes(userStore[userCount].salt, SALT_SIZE) != 1) {
            return false;
        }
        
        // Hash password with salt
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, userStore[userCount].salt, SALT_SIZE);
        SHA256_Update(&sha256, password, strlen(password));
        SHA256_Final(userStore[userCount].passwordHash, &sha256);
        
        // Store username
        strncpy(userStore[userCount].username, username, sizeof(userStore[userCount].username) - 1);
        userStore[userCount].isUsed = true;
        userCount++;
        
        return true;
    } catch(...) {
        return false;
    }
}

int main() {
    // Test cases
    printf("Test 1: %s\\n", signup("user1", "password123") ? "true" : "false"); // Should return true
    printf("Test 2: %s\\n", signup("user1", "password456") ? "true" : "false"); // Should return false (duplicate username)
    printf("Test 3: %s\\n", signup("", "password789") ? "true" : "false"); // Should return false (empty username)
    printf("Test 4: %s\\n", signup("user2", "") ? "true" : "false"); // Should return false (empty password)
    printf("Test 5: %s\\n", signup("user3", "strongpassword") ? "true" : "false"); // Should return true
    
    return 0;
}
