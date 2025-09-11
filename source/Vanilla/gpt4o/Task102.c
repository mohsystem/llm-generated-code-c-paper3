#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct {
    char username[50];
    char password[SHA256_DIGEST_LENGTH*2 + 1];
} User;

User database[5];

char* hashPassword(const char* password, char* outputBuffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
    return outputBuffer;
}

void updatePassword(const char* username, const char* newPassword, int index) {
    char hashedPassword[65];
    hashPassword(newPassword, hashedPassword);
    strcpy(database[index].username, username);
    strcpy(database[index].password, hashedPassword);
    printf("Password updated for user: %s\n", username);
}

int main() {
    updatePassword("user1", "password123", 0);
    updatePassword("user2", "mysecurepassword", 1);
    updatePassword("user3", "123456", 2);
    updatePassword("user4", "letmein", 3);
    updatePassword("user5", "password", 4);
    return 0;
}