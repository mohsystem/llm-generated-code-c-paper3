#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <stdbool.h>

// Simplified user storage (insecure for real-world use)
typedef struct {
    char username[256];
    char hashedPassword[SHA256_DIGEST_LENGTH*2 + 1]; 
} User;

#define MAX_USERS 100
User users[MAX_USERS];
int numUsers = 0;


bool authenticate(const char *username, const char *password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0) {
            char hashedPassword[SHA256_DIGEST_LENGTH*2 + 1];
            hashPassword(password, hashedPassword);
            return strcmp(hashedPassword, users[i].hashedPassword) == 0;
        }
    }
    return false; // Username not found
}

void hashPassword(const char *password, char* output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[SHA256_DIGEST_LENGTH*2] = '\0';
}

void addUser(const char *username, const char *password) {
     if (numUsers < MAX_USERS) {
        strcpy(users[numUsers].username, username);
        hashPassword(password, users[numUsers].hashedPassword);
        numUsers++;
    } else {
        // Handle error (max users reached)
        fprintf(stderr, "Error: Maximum number of users reached.\n");
    }
}


int main() {
    addUser("user1", "password123");
    addUser("user2", "securepass");
    addUser("admin", "adminpass");


    printf("%s\n", authenticate("user1", "password123") ? "true" : "false"); // True
    printf("%s\n", authenticate("user2", "wrongpass") ? "true" : "false");   // False
    printf("%s\n", authenticate("user3", "anypass") ? "true" : "false");   // False
    printf("%s\n", authenticate("admin", "adminpass") ? "true" : "false");  // True
    printf("%s\n", authenticate("user1", "password12") ? "true" : "false"); // False
    

    return 0;
}