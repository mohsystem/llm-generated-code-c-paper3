#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

void bytesToHex(char* dest, const unsigned char* bytes, int len) {
    for (int i = 0; i < len; i++) {
        sprintf(dest + i * 2, "%02x", bytes[i]);
    }
    dest[len * 2] = '\0';
}

void hashPassword(const char* password, const unsigned char* salt, char* hash) {
    unsigned char hashBytes[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Update(&sha256, salt, 16);
    SHA256_Final(hashBytes, &sha256);
    bytesToHex(hash, hashBytes, SHA256_DIGEST_LENGTH);
}

void signUp(const char* username, const char* password, char* saltHex, char* passwordHash) {
    unsigned char salt[16];
    RAND_bytes(salt, 16);
    bytesToHex(saltHex, salt, 16);
    hashPassword(password, salt, passwordHash);
}

int main() {
    // Test cases
    const char* usernames[] = {"user1", "user2", "user3", "user4", "user5"};
    const char* passwords[] = {"password1", "password2", "password3", "password4", "password5"};

    for (int i = 0; i < 5; i++) {
        char saltHex[33];
        char passwordHash[65];
        signUp(usernames[i], passwords[i], saltHex, passwordHash);
        printf("Username: %s, Salt: %s, Hash: %s\n", usernames[i], saltHex, passwordHash);
    }

    return 0;
}