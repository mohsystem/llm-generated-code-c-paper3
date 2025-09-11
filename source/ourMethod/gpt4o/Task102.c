#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#define MAX_USERS 100
#define USERNAME_LEN 50
#define HASH_LEN SHA256_DIGEST_LENGTH*2+1

typedef struct {
    char username[USERNAME_LEN];
    char passwordHash[HASH_LEN];
} User;

User database[MAX_USERS];
int userCount = 0;

void hashPassword(const char* password, char* outputBuffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[HASH_LEN - 1] = 0;
}

int updatePassword(const char* username, const char* newPassword) {
    char hashedPassword[HASH_LEN];
    hashPassword(newPassword, hashedPassword);

    for (int i = 0; i < userCount; ++i) {
        if (strcmp(database[i].username, username) == 0) {
            strcpy(database[i].passwordHash, hashedPassword);
            return 1;
        }
    }

    if (userCount < MAX_USERS) {
        strcpy(database[userCount].username, username);
        strcpy(database[userCount].passwordHash, hashedPassword);
        ++userCount;
        return 1;
    }

    return 0;
}

int main() {
    printf("%d\n", updatePassword("user1", "newPassword1"));
    printf("%d\n", updatePassword("user2", "newPassword2"));
    printf("%d\n", updatePassword("user3", "newPassword3"));
    printf("%d\n", updatePassword("user4", "newPassword4"));
    printf("%d\n", updatePassword("user5", "newPassword5"));

    return 0;
}