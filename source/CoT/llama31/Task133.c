#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <openssl/sha.h>
#include <base64.h>

typedef struct {
    char email[256];
    char password[256];
} User;

typedef struct {
    char token[256];
    char email[256];
    long long expiry;
} ResetToken;

User users[10];
int userCount = 0;

ResetToken resetTokens[10];
int resetTokenCount = 0;

void registerUser(const char* email, const char* password) {
    if (userCount < 10) {
        strcpy(users[userCount].email, email);
        strcpy(users[userCount].password, hashPassword(password));
        userCount++;
    }
}

void requestPasswordReset(const char* email) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0) {
            char token[256];
            generateResetToken(token);
            strcpy(resetTokens[resetTokenCount].token, token);
            strcpy(resetTokens[resetTokenCount].email, email);
            resetTokens[resetTokenCount].expiry = time(NULL) + 3600; // 1 hour
            resetTokenCount++;
            printf("Password reset token sent: %s\n", token);
            return;
        }
    }
    printf("User not found.\n");
}

void resetPassword(const char* email, const char* newPassword, const char* token) {
    for (int i = 0; i < resetTokenCount; i++) {
        if (strcmp(resetTokens[i].token, token) == 0) {
            if (strcmp(resetTokens[i].email, email) == 0 && resetTokens[i].expiry > time(NULL)) {
                for (int j = 0; j < userCount; j++) {
                    if (strcmp(users[j].email, email) == 0) {
                        strcpy(users[j].password, hashPassword(newPassword));
                        // Remove token from list
                        for (int k = i; k < resetTokenCount - 1; k++) {
                            resetTokens[k] = resetTokens[k + 1];
                        }
                        resetTokenCount--;
                        printf("Password reset successfully.\n");
                        return;
                    }
                }
            } else {
                printf("Token has expired or is invalid.\n");
            }
        }
    }
    printf("Token not found.\n");
}

void generateResetToken(char* token) {
    for (int i = 0; i < 64; i++) {
        token[i] = rand() % 256;
    }
    token[64] = '\0';
    base64_encode(token, token, 64);
}

void hashPassword(const char* password, char* hashedPassword) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    base64_encode(hash, hashedPassword, SHA256_DIGEST_LENGTH);
}

int main() {
    // Test cases
    registerUser("user1@example.com", "password123");
    registerUser("user2@example.com", "password456");
    requestPasswordReset("user1@example.com");
    requestPasswordReset("user2@example.com");
    resetPassword("user1@example.com", "newPassword123", "token");
    resetPassword("user2@example.com", "newPassword456", "token");
    return 0;
}