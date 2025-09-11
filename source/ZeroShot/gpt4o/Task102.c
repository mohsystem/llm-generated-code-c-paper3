#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERS 100

typedef struct {
    char username[50];
    char password[65];
} User;

User database[MAX_USERS];
int user_count = 0;

void hashPassword(const char* password, char* outputBuffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

void updatePassword(const char* username, const char* newPassword) {
    char hashedPassword[65];
    hashPassword(newPassword, hashedPassword);

    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].username, username) == 0) {
            strcpy(database[i].password, hashedPassword);
            return;
        }
    }

    strcpy(database[user_count].username, username);
    strcpy(database[user_count].password, hashedPassword);
    user_count++;
}

int main() {
    updatePassword("user1", "securePassword1");
    updatePassword("user2", "securePassword2");
    updatePassword("user3", "securePassword3");
    updatePassword("user4", "securePassword4");
    updatePassword("user5", "securePassword5");

    for (int i = 0; i < user_count; ++i) {
        printf("%s: %s\n", database[i].username, database[i].password);
    }

    return 0;
}