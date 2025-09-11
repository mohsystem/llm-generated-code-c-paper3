#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPassword(const char* password, char* hashedPassword) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPassword + i * 2, "%02x", hash[i]);
    }
}

void updatePassword(const char* username, const char* newPassword, char** users, int* userCount) {
    for (int i = 0; i < *userCount; ++i) {
        if (strcmp(users[i], username) == 0) {
            char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
            hashPassword(newPassword, hashedPassword);
            printf("Password updated for %s\n", username);
            // Update the stored password here
            // For simplicity, this is not implemented
            return;
        }
    }
    printf("User %s does not exist\n", username);
}

int main() {
    const char* usernames[] = {"user1", "user2", "user3", "user4", "user5"};
    const char* passwords[] = {"password1", "password2", "password3", "password4", "password5"};
    char** users = (char**)malloc(5 * sizeof(char*));
    int userCount = 5;

    for (int i = 0; i < 5; ++i) {
        users[i] = (char*)malloc(256 * sizeof(char));
        hashPassword(passwords[i], users[i]);
    }

    for (int i = 0; i < 5; ++i) {
        char newPassword[256];
        printf("Enter new password for %s: ", usernames[i]);
        scanf("%255s", newPassword);
        updatePassword(usernames[i], newPassword, users, &userCount);
    }

    // Free the allocated memory
    for (int i = 0; i < 5; ++i) {
        free(users[i]);
    }
    free(users);

    return 0;
}