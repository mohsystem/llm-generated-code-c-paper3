#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct {
    char username[50];
    char hashedPassword[65];
} User;

User database[5];
int userCount = 0;

int updatePassword(const char *username, const char *newPassword) {
    char hashedPassword[65];
    hashPassword(newPassword, hashedPassword);
    strcpy(database[userCount].username, username);
    strcpy(database[userCount].hashedPassword, hashedPassword);
    userCount++;
    return 1;
}

void hashPassword(const char *password, char *output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)password, strlen(password), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        sprintf(output + (i * 2), "%02x", hash[i]);
    output[64] = 0;
}

int main() {
    printf("%d\n", updatePassword("user1", "password123"));
    printf("%d\n", updatePassword("user2", "newpassword456"));
    printf("%d\n", updatePassword("user3", "anotherpassword789"));
    printf("%d\n", updatePassword("user4", "yetanotherpassword012"));
    printf("%d\n", updatePassword("user5", "lastpassword345"));
    return 0;
}