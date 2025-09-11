#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <openssl/pbkdf2.h>

void hashPassword(const char* password, char* hashedPassword) {
    unsigned char salt[32];
    RAND_bytes(salt, 32);

    unsigned char hash[32];
    PKCS5_PBKDF2_HMAC_SHA1(password, strlen(password), salt, 32, 1000, 32, hash);

    // Convert salt and hash to hex
    char saltStr[65];
    for (int i = 0; i < 32; ++i) {
        sprintf(saltStr + i * 2, "%02x", salt[i]);
    }

    char hashStr[65];
    for (int i = 0; i < 32; ++i) {
        sprintf(hashStr + i * 2, "%02x", hash[i]);
    }

    sprintf(hashedPassword, "%s:%s", saltStr, hashStr);
}

bool verifyPassword(const char* password, const char* hashedPassword) {
    char* colon = strchr(hashedPassword, ':');
    if (!colon) return false;

    char saltStr[65];
    strncpy(saltStr, hashedPassword, colon - hashedPassword);
    saltStr[colon - hashedPassword] = '\0';

    char expectedHashStr[65];
    strcpy(expectedHashStr, colon + 1);

    unsigned char salt[32];
    for (int i = 0; i < 32; ++i) {
        salt[i] = static_cast<unsigned char>(strtoul(saltStr + i * 2, NULL, 16));
    }

    unsigned char hash[32];
    PKCS5_PBKDF2_HMAC_SHA1(password, strlen(password), salt, 32, 1000, 32, hash);

    char actualHashStr[65];
    for (int i = 0; i < 32; ++i) {
        sprintf(actualHashStr + i * 2, "%02x", hash[i]);
    }

    return strcmp(actualHashStr, expectedHashStr) == 0;
}

int main() {
    // Test cases
    const char* usernames[] = {"user1", "user2", "user3", "user4", "user5"};
    const char* passwords[] = {"password1", "password2", "password3", "password4", "password5"};

    for (int i = 0; i < 5; ++i) {
        char hashedPassword[129];
        hashPassword(passwords[i], hashedPassword);
        printf("Username: %s, Hashed Password: %s\n", usernames[i], hashedPassword);
    }

    return 0;
}