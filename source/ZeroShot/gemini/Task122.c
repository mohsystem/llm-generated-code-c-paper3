#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Simplified representation for demonstration (insecure in a real application)
#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define SALT_LENGTH 16

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char salt[SALT_LENGTH * 2 + 1]; // Store salt as hex string
    char hashed_password[SHA256_DIGEST_LENGTH * 2 + 1]; // Store hash as hex string
} User;

User users[MAX_USERS];
int num_users = 0;


char* generate_salt() {
    char* salt = malloc(SALT_LENGTH * 2 + 1); 
    if (!salt) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE); 
    }

    const char* hex_chars = "0123456789abcdef";
    for (int i = 0; i < SALT_LENGTH * 2; i++) {
        salt[i] = hex_chars[rand() % 16];
    }
    salt[SALT_LENGTH * 2] = '\0';
    return salt;
}



char* hash_password(const char* password, const char* salt) {
    char salted_password[MAX_PASSWORD_LENGTH + SALT_LENGTH * 2 + 1]; // Adjust size
    strcpy(salted_password, salt);
    strcat(salted_password, password);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(salted_password, strlen(salted_password), hash);

    char* hex_hash = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
     if (!hex_hash) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE); 
    }
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_hash + i * 2, "%02x", hash[i]);
    }
    hex_hash[SHA256_DIGEST_LENGTH * 2] = '\0';
    return hex_hash;
}



const char* signup(const char* username, const char* password) {
    for (int i = 0; i < num_users; i++) {
        if (strcmp(username, users[i].username) == 0) {
            return "Username already exists.";
        }
    }

    if (num_users >= MAX_USERS) {
        return "User database full.";
    }

    char* salt = generate_salt();
    char* hashed_password = hash_password(password, salt);


    strncpy(users[num_users].username, username, MAX_USERNAME_LENGTH -1);
    users[num_users].username[MAX_USERNAME_LENGTH - 1] = '\0'; // Ensure null termination
    strncpy(users[num_users].salt, salt, SALT_LENGTH * 2);
    users[num_users].salt[SALT_LENGTH * 2] = '\0'; // Ensure null-termination
    strncpy(users[num_users].hashed_password, hashed_password, SHA256_DIGEST_LENGTH * 2 );
    users[num_users].hashed_password[SHA256_DIGEST_LENGTH * 2] = '\0'; // Ensure null-termination
    
    num_users++;

    free(salt); // Free allocated memory
    free(hashed_password);
    return "Signup successful.";
}


int main() {
    srand(time(NULL)); // Seed the random number generator
    printf("%s\n", signup("user1", "password123"));
    printf("%s\n", signup("user2", "securepass"));
    printf("%s\n", signup("user1", "anotherpass")); // Username already exists
    printf("%s\n", signup("user3", "p@$$wOrd"));
    printf("%s\n", signup("user4", "12345678"));

    return 0;
}