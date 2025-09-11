
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_HASH_LENGTH 65
#define MIN_PASSWORD_LENGTH 8

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password_hash[MAX_HASH_LENGTH];
};

struct Auth {
    struct User users[MAX_USERS];
    int user_count;
};

void init_auth(struct Auth* auth) {
    auth->user_count = 0;
}

void hash_password(const char* password, char* hash_output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash_output + (i * 2), "%02x", hash[i]);
    }
    hash_output[64] = 0;
}

int register_user(struct Auth* auth, const char* username, const char* password) {
    if (!username || !password || strlen(password) < MIN_PASSWORD_LENGTH || 
        auth->user_count >= MAX_USERS) {
        return 0;
    }
    
    // Check if username already exists
    for(int i = 0; i < auth->user_count; i++) {
        if(strcmp(auth->users[i].username, username) == 0) {
            return 0;
        }
    }
    
    strcpy(auth->users[auth->user_count].username, username);
    hash_password(password, auth->users[auth->user_count].password_hash);
    auth->user_count++;
    return 1;
}

int authenticate(struct Auth* auth, const char* username, const char* password) {
    if (!username || !password) {
        return 0;
    }
    
    char hashed_password[MAX_HASH_LENGTH];
    hash_password(password, hashed_password);
    
    for(int i = 0; i < auth->user_count; i++) {
        if(strcmp(auth->users[i].username, username) == 0) {
            return strcmp(auth->users[i].password_hash, hashed_password) == 0;
        }
    }
    return 0;
}

int main() {
    struct Auth auth;
    init_auth(&auth);
    
    // Test case 1: Successful registration
    printf("%d\\n", register_user(&auth, "user1", "password123")); // 1
    
    // Test case 2: Successful authentication
    printf("%d\\n", authenticate(&auth, "user1", "password123")); // 1
    
    // Test case 3: Failed authentication - wrong password
    printf("%d\\n", authenticate(&auth, "user1", "wrongpass")); // 0
    
    // Test case 4: Failed registration - username already exists
    printf("%d\\n", register_user(&auth, "user1", "newpassword")); // 0
    
    // Test case 5: Failed registration - password too short
    printf("%d\\n", register_user(&auth, "user2", "short")); // 0
    
    return 0;
}
