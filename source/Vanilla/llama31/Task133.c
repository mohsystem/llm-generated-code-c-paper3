#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char email[100];
    long long expiry;
} PasswordResetToken;

void sendPasswordResetEmail(const char* email, const char* token) {
    printf("Sending password reset email to %s with token %s\n", email, token);
}

int verifyPasswordResetToken(const char* token, const char* newPassword, PasswordResetToken* tokens, int numTokens) {
    for (int i = 0; i < numTokens; i++) {
        if (strcmp(tokens[i].email, token) == 0) {
            long long now = time(NULL);
            if (now > tokens[i].expiry) {
                return 0;
            }

            // Update password logic here
            printf("Updating password for %s\n", tokens[i].email);
            return 1;
        }
    }
    return 0;
}

void generatePasswordResetToken(const char* email, PasswordResetToken* tokens, int* numTokens) {
    static char token[65];
    for (int i = 0; i < 64; i++) {
        token[i] = 'a' + (rand() % 26);
    }
    token[64] = '\0';

    long long expiry = time(NULL) + 30 * 60; // 30 minutes
    strcpy(tokens[*numTokens].email, email);
    tokens[*numTokens].expiry = expiry;
    (*numTokens)++;

    sendPasswordResetEmail(email, token);
}

int main() {
    srand(time(NULL));
    PasswordResetToken tokens[10];
    int numTokens = 0;

    generatePasswordResetToken("user@example.com", tokens, &numTokens);
    if (verifyPasswordResetToken("user@example.com", "newpassword", tokens, numTokens)) {
        printf("Password reset successfully.\n");
    } else {
        printf("Password reset failed.\n");
    }

    return 0;
}