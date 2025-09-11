#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <openssl/sha.h>

// Note: This C implementation uses a simplified, insecure approach for demonstration
// due to the complexity of securely managing user credentials in C without external libraries.
// In a real-world application, use a dedicated library for secure password hashing and storage.

typedef struct {
    char username[50];
    char salt[33]; // Store salt as hex string
    char hashed_password[65]; // Store hashed password as hex string
} User;


User users[100]; // Fixed-size array for simplicity (insecure in real applications)
int num_users = 0;


bool register_user(const char *username, const char *password) {
    // Check if username already exists (insecure comparison)
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0) {
            return false;
        }
    }

    // "Salt" generation (insecure)
    char salt[17];
    for (int i = 0; i < 16; i++) {
        salt[i] = 'a' + (rand() % 26); // Generate random lowercase letters (insecure)
    }
    salt[16] = '\0';


    // Password hashing (insecure)
    char salted_password[67];
    strcpy(salted_password, salt);
    strcat(salted_password, password);


    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(hash, &sha256);


    char hashed_password_hex[65];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed_password_hex + (i * 2), "%02x", hash[i]);
    }

    // Store user credentials (insecure)
    if (num_users < 100) {
        strcpy(users[num_users].username, username);
        strcpy(users[num_users].salt, salt);
        strcpy(users[num_users].hashed_password, hashed_password_hex);
        num_users++;
        return true;
    } else {
        return false; // Array full
    }

}

bool authenticate_user(const char *username, const char *password) {
     for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0) {

            char salted_password[67];
            strcpy(salted_password, users[i].salt);
            strcat(salted_password, password);

            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256_CTX sha256;
            SHA256_Init(&sha256);
            SHA256_Update(&sha256, salted_password, strlen(salted_password));
            SHA256_Final(hash, &sha256);

            char hashed_password_hex[65];
            for (int j = 0; j < SHA256_DIGEST_LENGTH; j++) {
                sprintf(hashed_password_hex + (j * 2), "%02x", hash[j]);
            }

            if(strcmp(hashed_password_hex, users[i].hashed_password) == 0)
                return true;
            else
                return false;
        }
    }
    return false;
}


int main() {
    // Test cases
    register_user("user1", "password123");
    register_user("user2", "P@$$wOrd");
    register_user("bob", "bobspassword");

    printf("%d\n", authenticate_user("user1", "password123")); // Expected: true (1)
    printf("%d\n", authenticate_user("user1", "wrongpassword")); // Expected: false (0)
    printf("%d\n", authenticate_user("user2", "P@$$wOrd")); // Expected: true (1)
    printf("%d\n", authenticate_user("nonexistentuser", "password")); // Expected: false (0)
    printf("%d\n", authenticate_user("bob", "bobspassword")); // Expected: true (1)


    return 0;
}