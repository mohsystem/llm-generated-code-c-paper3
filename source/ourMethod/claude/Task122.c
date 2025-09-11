
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <ctype.h>

#define MAX_USERS 100
#define MIN_PASSWORD_LENGTH 8
#define SALT_LENGTH 16
#define HASH_LENGTH (SHA256_DIGEST_LENGTH * 2)
#define SALT_HEX_LENGTH (SALT_LENGTH * 2)

struct User {
    char username[50];
    char passwordHash[HASH_LENGTH + 1];
    char salt[SALT_HEX_LENGTH + 1];
    bool isActive;
};

struct Task122 {
    struct User users[MAX_USERS];
    int userCount;
};

bool isPasswordStrong(const char* password) {
    if (strlen(password) < MIN_PASSWORD_LENGTH) {
        return false;
    }
    
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
        else if (strchr("@#$%^&+=", password[i])) hasSpecial = true;
    }
    
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

void generateSalt(char* salt) {
    unsigned char rawSalt[SALT_LENGTH];
    RAND_bytes(rawSalt, SALT_LENGTH);
    
    for (int i = 0; i < SALT_LENGTH; i++) {
        sprintf(salt + (i * 2), "%02x", rawSalt[i]);
    }
    salt[SALT_HEX_LENGTH] = '\\0';
}

void hashPassword(const char* password, const char* salt, char* hash) {
    char combined[512];
    snprintf(combined, sizeof(combined), "%s%s", password, salt);
    
    unsigned char hashBytes[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, combined, strlen(combined));
    SHA256_Final(hashBytes, &sha256);
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hash + (i * 2), "%02x", hashBytes[i]);
    }
    hash[HASH_LENGTH] = '\\0';
}

bool signUp(struct Task122* manager, const char* username, const char* password) {
    if (!username || !password || strlen(username) == 0) {
        return false;
    }
    
    // Check if user exists
    for (int i = 0; i < manager->userCount; i++) {
        if (manager->users[i].isActive && strcmp(manager->users[i].username, username) == 0) {
            return false;
        }
    }
    
    // Validate password strength
    if (!isPasswordStrong(password)) {
        return false;
    }
    
    // Check if we have space for new user
    if (manager->userCount >= MAX_USERS) {
        return false;
    }
    
    struct User* newUser = &manager->users[manager->userCount];
    
    // Generate salt and hash password
    generateSalt(newUser->salt);
    hashPassword(password, newUser->salt, newUser->passwordHash);
    
    // Store user data
    strncpy(newUser->username, username, sizeof(newUser->username) - 1);
    newUser->username[sizeof(newUser->username) - 1] = '\\0';
    newUser->isActive = true;
    
    manager->userCount++;
    return true;
}

int main() {
    struct Task122 manager = {0};
    
    // Test cases
    printf("%d\\n", signUp(&manager, "user1", "Secure@Pass123")); // Should print 1
    printf("%d\\n", signUp(&manager, "user2", "weak")); // Should print 0
    printf("%d\\n", signUp(&manager, "user1", "Another@Pass123")); // Should print 0
    printf("%d\\n", signUp(&manager, "user3", "NoSpecialChar123")); // Should print 0
    printf("%d\\n", signUp(&manager, "user4", "Secure@Pass123!")); // Should print 1
    
    return 0;
}
