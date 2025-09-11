#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <stdlib.h>

void getSaltedPasswordHash(const char* password, const char* salt, unsigned char* hash) {
    char salted_password[256]; // Adjust size as needed
    snprintf(salted_password, sizeof(salted_password), "%s%s", salt, password);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(hash, &sha256);
}

void generateSalt(char* salt, size_t salt_len) {
     for (size_t i = 0; i < salt_len; ++i) {
        salt[i] = (char)(rand() % 256); 
    }
    salt[salt_len-1] = '\0';
}



int main() {
    char passwords[][32] = {"password123", "test", "anotherPassword", "123456", "complexPassword"};
    int num_passwords = sizeof(passwords) / sizeof(passwords[0]);

    for (int i = 0; i < num_passwords; i++) {
        char salt[17];
        unsigned char saltedHash[SHA256_DIGEST_LENGTH];
        generateSalt(salt,sizeof(salt));
        getSaltedPasswordHash(passwords[i], salt, saltedHash);

        printf("Password: %s\n", passwords[i]);
        printf("Salt: %s\n", salt);
        printf("Salted Hash: ");
        for (int j = 0; j < SHA256_DIGEST_LENGTH; j++) {
            printf("%02x", saltedHash[j]);
        }
        printf("\n\n");
    }
    return 0;
}