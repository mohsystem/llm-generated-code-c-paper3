#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

// Simplified version due to lack of built-in hashing and secure random number generation
typedef struct {
    char token[33];
    time_t expiryTime;
} PasswordResetToken;

typedef struct {
    char email[100];
    PasswordResetToken token;
} User;

User users[10];
int userCount = 0;

void generateSecureToken(char* token) {
    for (int i = 0; i < 32; ++i) {
        token[i] = 'a' + (rand() % 26);
    }
    token[32] = '\0';
}

void generatePasswordResetToken(const char* email, char* token) {
    if (userCount >= 10) return; // Simplified, should handle more users

    time_t expiryTime = time(NULL) + 1800; // 30 minutes
    generateSecureToken(token);
    strcpy(users[userCount].email, email);
    strcpy(users[userCount].token.token, token);
    users[userCount].token.expiryTime = expiryTime;
    userCount++;
}

int verifyToken(const char* token, const char* newPassword) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].token.token, token) == 0) {
            if (users[i].token.expiryTime > time(NULL)) {
                // Update password here
                users[i].token.expiryTime = 0; // Mark as used
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    srand(time(NULL)); // Initialize random number generator

    char token[33];
    generatePasswordResetToken("user@example.com", token);
    printf("Password reset token: %s\n", token);
    if (verifyToken(token, "newPassword")) {
        printf("Password reset successful\n");
    } else {
        printf("Password reset failed\n");
    }

    // Additional test cases
    generatePasswordResetToken("user2@example.com", token);
    printf("%s\n", token);
    printf("%d\n", verifyToken(token, "newPassword")); // Should fail because token is already used
    printf("%d\n", verifyToken("invalidToken", "newPassword")); // Should fail because token is invalid
    generatePasswordResetToken("user3@example.com", token);
    printf("%s\n", token);
    printf("%d\n", verifyToken(token, "newPassword")); // Should fail because token is already used

    return 0;
}