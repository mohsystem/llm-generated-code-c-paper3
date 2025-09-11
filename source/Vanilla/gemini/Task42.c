#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <stdbool.h>

// A simple representation of a user database (in real applications, use a more robust solution).
typedef struct {
    char username[50];
    unsigned char password_hash[SHA256_DIGEST_LENGTH];
} User;

#define MAX_USERS 100
User user_db[MAX_USERS];
int num_users = 0;


unsigned char* hash_password(const char* password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    unsigned char *result = (unsigned char*)malloc(SHA256_DIGEST_LENGTH);
    memcpy(result, hash, SHA256_DIGEST_LENGTH);
    return result;
}

bool register_user(const char* username, const char* password) {
    if (num_users < MAX_USERS) {
        for (int i = 0; i < num_users; i++) {
            if (strcmp(username, user_db[i].username) == 0) {
                return false; // Username already exists
            }
        }
        strcpy(user_db[num_users].username, username);
        unsigned char *hashed_password = hash_password(password);
        memcpy(user_db[num_users].password_hash, hashed_password, SHA256_DIGEST_LENGTH);
        free(hashed_password);
        num_users++;
        return true;
    }
    return false; // User database full
}

bool authenticate_user(const char* username, const char* password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, user_db[i].username) == 0) {
            unsigned char* hashed_password = hash_password(password);
            bool match = (memcmp(hashed_password, user_db[i].password_hash, SHA256_DIGEST_LENGTH) == 0);
            free(hashed_password);
            return match;
        }
    }
    return false; // User not found
}

int main() {
     register_user("user1", "password123");
    register_user("user2", "securepass");

    printf("%d\n", authenticate_user("user1", "password123")); // 1 (true)
    printf("%d\n", authenticate_user("user1", "wrongpass")); // 0 (false)
    printf("%d\n", authenticate_user("user2", "securepass")); // 1 (true)
    printf("%d\n", authenticate_user("user3", "pass")); // 0 (false)
    printf("%d\n", register_user("user1", "newpass")); // 0 (false)
    

    return 0;
}