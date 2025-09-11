
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <stdbool.h>

#define SALT_LENGTH 32
#define HASH_LENGTH SHA256_DIGEST_LENGTH
#define MIN_PASSWORD_LENGTH 8
#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 32
#define MAX_PASSWORD_LENGTH 64

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    unsigned char salt[SALT_LENGTH];
    unsigned char password_hash[HASH_LENGTH];
    bool is_active;
} User;

typedef struct {
    User users[MAX_USERS];
    int user_count;
} Task42;

void generate_salt(unsigned char* salt) {
    RAND_bytes(salt, SALT_LENGTH);
}

void hash_password(const char* password, const unsigned char* salt, unsigned char* hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

bool register_user(Task42* auth, const char* username, const char* password) {
    if (!username || !password || strlen(password) < MIN_PASSWORD_LENGTH ||
        strlen(username) >= MAX_USERNAME_LENGTH || strlen(password) >= MAX_PASSWORD_LENGTH) {
        return false;
    }
    
    // Check for existing username
    for (int i = 0; i < auth->user_count; i++) {
        if (auth->users[i].is_active && strcmp(auth->users[i].username, username) == 0) {
            return false;
        }
    }
    
    if (auth->user_count >= MAX_USERS) {
        return false;
    }
    
    User* new_user = &auth->users[auth->user_count];
    strncpy(new_user->username, username, MAX_USERNAME_LENGTH - 1);
    new_user->username[MAX_USERNAME_LENGTH - 1] = '\\0';
    
    generate_salt(new_user->salt);
    hash_password(password, new_user->salt, new_user->password_hash);
    new_user->is_active = true;
    
    auth->user_count++;
    return true;
}

bool authenticate(Task42* auth, const char* username, const char* password) {
    if (!username || !password) {
        return false;
    }
    
    for (int i = 0; i < auth->user_count; i++) {
        if (auth->users[i].is_active && strcmp(auth->users[i].username, username) == 0) {
            unsigned char hash[HASH_LENGTH];
            hash_password(password, auth->users[i].salt, hash);
            return memcmp(hash, auth->users[i].password_hash, HASH_LENGTH) == 0;
        }
    }
    
    return false;
}

int main() {
    Task42 auth = {.user_count = 0};
    
    // Test case 1: Register new user
    printf("Test 1: %d\\n", register_user(&auth, "user1", "password123"));
    
    // Test case 2: Register duplicate user
    printf("Test 2: %d\\n", register_user(&auth, "user1", "password456"));
    
    // Test case 3: Register with invalid password
    printf("Test 3: %d\\n", register_user(&auth, "user2", "pass"));
    
    // Test case 4: Authenticate valid user
    printf("Test 4: %d\\n", authenticate(&auth, "user1", "password123"));
    
    // Test case 5: Authenticate with wrong password
    printf("Test 5: %d\\n", authenticate(&auth, "user1", "wrongpass"));
    
    return 0;
}
