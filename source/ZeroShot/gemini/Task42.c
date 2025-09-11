#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <stdbool.h>

// Simplified representation of a user database (insecure for real-world use)
typedef struct {
    char username[256];
    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1]; 
} User;

#define MAX_USERS 100
User users[MAX_USERS];
int numUsers = 0;


bool registerUser(const char *username, const char *password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return false; // Username already exists
        }
    }

    if (numUsers >= MAX_USERS) {
        return false; // Database full (in this simplified example)
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    // Convert hash to hexadecimal string
     for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(users[numUsers].hashedPassword + (i * 2), "%02x", hash[i]);
    }
    

    strcpy(users[numUsers].username, username);
    numUsers++;
    return true;
}

bool authenticateUser(const char *username, const char *password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
             unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256_CTX sha256;
            SHA256_Init(&sha256);
            SHA256_Update(&sha256, password, strlen(password));
            SHA256_Final(hash, &sha256);

            char hexString[SHA256_DIGEST_LENGTH * 2 + 1];
             for (int j = 0; j < SHA256_DIGEST_LENGTH; j++) {
                sprintf(hexString + (j * 2), "%02x", hash[j]);
            }

            return strcmp(users[i].hashedPassword, hexString) == 0;
        }
    }
    return false; // User not found
}


int main() {
     registerUser("user1", "password123");
    registerUser("user2", "securepass");

    printf("%d\n", authenticateUser("user1", "password123")); // True
    printf("%d\n", authenticateUser("user1", "wrongpass"));   // False
    printf("%d\n", authenticateUser("user2", "securepass"));  // True
    printf("%d\n", authenticateUser("user3", "anypass"));    // False (user doesn't exist)
    printf("%d\n", registerUser("user1", "newpass"));      // False (username already exists)


    return 0;
}