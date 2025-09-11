#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

char* getSaltedHash(const char* password, const char* salt) {
    size_t password_len = strlen(password);
    size_t salt_len = strlen(salt);
    char* salted_password = (char*)malloc(salt_len + password_len + 1);
    if (!salted_password) {
        return NULL; // Handle memory allocation failure
    }

    strcpy(salted_password, salt);
    strcat(salted_password, password);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(hash, &sha256);
    free(salted_password);

    char* hex_hash = (char*)malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    if (!hex_hash) {
        return NULL; // Handle memory allocation failure
    }

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_hash + i * 2, "%02x", hash[i]);
    }
    return hex_hash;

}

char* generateSalt() {
    char* salt = (char*)malloc(17); // 16 bytes + null terminator
    if (!salt) {
        return NULL; // Handle memory allocation failure
    }

    for (int i = 0; i < 16; i++) {
        salt[i] = rand() % 256; // Generates a random byte
    }
    salt[16] = '\0';
    return salt;
}

int main() {
    const char* passwords[] = {"test1", "password123", "MyStrongPassword", "123456", "AnotherTest"};
    int num_passwords = sizeof(passwords) / sizeof(passwords[0]);

    for (int i = 0; i < num_passwords; i++) {
        char *salt = generateSalt();
        char *saltedHash = getSaltedHash(passwords[i], salt);

        if (salt && saltedHash) { // Check if allocation succeeded
            printf("Password: %s, Salt: %s, Hash: %s\n", passwords[i], salt, saltedHash);
            free(salt);
            free(saltedHash);
        } else {
            fprintf(stderr, "Memory allocation failed\n");
            return 1; // Indicate an error
        }
        
    }

    return 0;
}