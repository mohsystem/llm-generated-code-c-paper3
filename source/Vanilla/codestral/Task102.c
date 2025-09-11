// C code requires additional libraries and headers to handle database operations.
// This is a simplified example without actual database operations.

#include <stdio.h>
#include <openssl/sha.h>
#include <string.h>

void hashPassword(const char* password, unsigned char* hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

void updatePassword(const char* username, const char* newPassword) {
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    hashPassword(newPassword, hashedPassword);
    // Database operations to update the password here
    printf("Password updated successfully!\n");
}

int main() {
    updatePassword("user1", "newPassword1");
    updatePassword("user2", "newPassword2");
    updatePassword("user3", "newPassword3");
    updatePassword("user4", "newPassword4");
    updatePassword("user5", "newPassword5");
    return 0;
}