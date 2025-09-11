
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <openssl/sha.h>

#define MAX_ATTEMPTS 3
#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 128
#define HASH_LENGTH SHA256_DIGEST_LENGTH * 2 + 1

static int attemptCount = 0;
// Simulated user database - in real system use proper secure database
static char currentPasswordHash[HASH_LENGTH] = "5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8";

void bytesToHexString(unsigned char* bytes, int len, char* hex) {
    for(int i = 0; i < len; i++) {
        sprintf(hex + (i * 2), "%02x", bytes[i]);
    }
    hex[len * 2] = '\\0';
}

void hashPassword(const char* password, char* hash) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(digest, &ctx);
    bytesToHexString(digest, SHA256_DIGEST_LENGTH, hash);
}

bool isPasswordValid(const char* password) {
    if (strlen(password) < MIN_PASSWORD_LENGTH) {
        return false;
    }
    
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) hasUpper = true;
        else if (islower(password[i])) hasLower = true;
        else if (isdigit(password[i])) hasDigit = true;
        else hasSpecial = true;
    }
    
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

typedef struct {
    bool success;
    const char* message;
} ResetResult;

ResetResult resetPassword(const char* currentPassword, const char* newPassword) {
    ResetResult result = {false, NULL};
    char hashedPassword[HASH_LENGTH];
    
    // Check attempt count to prevent brute force
    if (attemptCount >= MAX_ATTEMPTS) {
        result.message = "Account locked due to too many attempts";
        return result;
    }
    
    // Validate inputs
    if (!currentPassword || !newPassword || 
        strlen(currentPassword) >= MAX_PASSWORD_LENGTH || 
        strlen(newPassword) >= MAX_PASSWORD_LENGTH) {
        result.message = "Invalid password input";
        return result;
    }
    
    // Validate current password
    hashPassword(currentPassword, hashedPassword);
    if (strcmp(hashedPassword, currentPasswor', type='text')