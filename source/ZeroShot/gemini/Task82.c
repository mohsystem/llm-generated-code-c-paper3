#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

unsigned char* getSaltedPasswordHash(const char* password, const unsigned char* salt, size_t salt_len) {
    size_t password_len = strlen(password);
    size_t salted_len = salt_len + password_len;
    unsigned char* salted_password = (unsigned char*)malloc(salted_len);
    memcpy(salted_password, salt, salt_len);
    memcpy(salted_password + salt_len, password, password_len);

    unsigned char* hash = (unsigned char*)malloc(SHA256_DIGEST_LENGTH);
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, salted_len);
    SHA256_Final(hash, &sha256);

    free(salted_password);
    return hash;
}

unsigned char* generateSalt(size_t salt_len) {
    unsigned char* salt = (unsigned char*)malloc(salt_len);
    for (size_t i = 0; i < salt_len; i++) {
        salt[i] = rand() % 256; 
    }
    return salt;
}

int main() {
    char *passwords[] = {"password123", "test", "securePassword", "1234567890", "MyStrongPassword"};
    int num_passwords = sizeof(passwords) / sizeof(passwords[0]);
    size_t salt_len = 16;

    for (int i = 0; i < num_passwords; i++) {
        unsigned char *salt = generateSalt(salt_len);
        unsigned char *saltedHash = getSaltedPasswordHash(passwords[i], salt, salt_len);

        printf("Password: %s\n", passwords[i]);
        printf("Salt: ");
        for (size_t j = 0; j < salt_len; j++) {
            printf("%d ", salt[j]);
        }
        printf("\n");
        printf("Salted Hash: ");
        for (int j = 0; j < SHA256_DIGEST_LENGTH; j++) {
            printf("%d ", saltedHash[j]);
        }
        printf("\n\n");

        free(salt);
        free(saltedHash);
    }

    return 0;
}