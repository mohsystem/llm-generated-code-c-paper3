// C does not have built-in support for hashing and secure random number generation.
// For a real-world application, consider using a library like OpenSSL or Crypto++.
// This example uses a simple XOR cipher for demonstration purposes only.

#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

char userDatabase[MAX_USERS][MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH];
int userCount = 0;

void xorCipher(char* str, int len, char key) {
    for (int i = 0; i < len; i++) {
        str[i] ^= key;
    }
}

void registerUser(const char* username, const char* password) {
    if (userCount < MAX_USERS) {
        strcpy(userDatabase[userCount], username);
        strcpy(userDatabase[userCount] + MAX_USERNAME_LENGTH, password);
        xorCipher(userDatabase[userCount] + MAX_USERNAME_LENGTH, strlen(password), 'K');
        userCount++;
    }
}

void resetPassword(const char* username, const char* newPassword) {
    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(userDatabase[i], username) == 0) {
            strcpy(userDatabase[i] + MAX_USERNAME_LENGTH, newPassword);
            xorCipher(userDatabase[i] + MAX_USERNAME_LENGTH, strlen(newPassword), 'K');
            printf("Password reset successful.\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("User not found.\n");
    }
}

int main() {
    // test cases
    registerUser("user1", "oldPassword1");
    registerUser("user2", "oldPassword2");
    resetPassword("user1", "newPassword1");
    resetPassword("user2", "newPassword2");
    return 0;
}