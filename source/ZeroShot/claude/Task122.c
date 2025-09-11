
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define MAX_USERS 100
#define SALT_SIZE 16
#define HASH_SIZE SHA256_DIGEST_LENGTH*2+1

typedef struct {
    char username[50];
    char password_hash[HASH_SIZE];
    unsigned char salt[SALT_SIZE];
    bool is_active;
} UserCredentials;

UserCredentials users[MAX_USERS];
int user_count = 0;

void bytes_to_hex(unsigned char* bytes, int len, char* hex) {
    for(int i = 0; i < len; i++) {
        sprintf(hex + (i * 2), "%02x", bytes[i]);
    }
    hex[len * 2] = 0;
}

bool signup(const char* username, const char* password) {
    if(!username || !password || strlen(password) < 8 || user_count >= MAX_USERS) {
        return false;
    }
    
    // Check if username exists
    for(int i = 0; i < user_count; i++) {
        if(users[i].is_active && strcmp(users[i].username, username) == 0) {
            return false;
        }
    }
    
    UserCredentials* new_user = &users[user_count];
    
    // Generate salt
    if(RAND_bytes(new_user->salt, SALT_SIZE) != 1) {
        return false;
    }
    
    // Hash password with salt
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, new_user->salt, SALT_SIZE);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    // Convert hash to hex string
    bytes_to_hex(hash, SHA256_DIGEST_LENGTH, new_user->password_hash);
    
    // Store user data
    strncpy(new_user->username, username, sizeof(new_user->username) - 1);
    new_user->is_active = true;
    user_count++;
    
    return true;
}

int main() {
    // Test case 1: Valid signup
    printf("Test 1: %d\\n", signup("user1", "strongpass123"));
    
    // Test case 2: Duplicate username
    printf("Test 2: %d\\n", signup("user1", "anotherpass456"));
    
    // Test case 3: Password too short
    printf("Test 3: %d\\n", signup("user2", "short"));
    
    // Test case 4: Empty username
    printf("Test 4: %d\\n", signup("", "validpass123"));
    
    // Test case 5: NULL values
    printf("Test 5: %d\\n", signup(NULL, NULL));
    
    return 0;
}
