#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

void hashPasswordWithSalt(const char* password, const char* salt, char* outputBuffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, strlen(salt));
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[64] = 0;
}

void generateSalt(char* saltBuffer, size_t length) {
    unsigned char salt[length];
    RAND_bytes(salt, length);
    for (size_t i = 0; i < length; i++) {
        sprintf(saltBuffer + (i * 2), "%02x", salt[i]);
    }
    saltBuffer[length * 2] = 0;
}

int main() {
    char salt[33];
    generateSalt(salt, 16);

    char hash[65];
    
    hashPasswordWithSalt("password1", salt, hash);
    printf("%s\n", hash);

    hashPasswordWithSalt("password2", salt, hash);
    printf("%s\n", hash);

    hashPasswordWithSalt("password3", salt, hash);
    printf("%s\n", hash);

    hashPasswordWithSalt("password4", salt, hash);
    printf("%s\n", hash);

    hashPasswordWithSalt("password5", salt, hash);
    printf("%s\n", hash);

    return 0;
}