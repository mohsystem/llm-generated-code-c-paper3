#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

void hash_password(const char *password, const char *salt, char *outputBuffer) {
    char saltedPassword[256];
    snprintf(saltedPassword, sizeof(saltedPassword), "%s%s", salt, password);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)saltedPassword, strlen(saltedPassword), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
    outputBuffer[SHA256_DIGEST_LENGTH * 2] = '\0';
}

void get_salt(char *saltBuffer) {
    unsigned char salt[16];
    RAND_bytes(salt, sizeof(salt));

    for (int i = 0; i < sizeof(salt); i++) {
        sprintf(saltBuffer + (i * 2), "%02x", salt[i]);
    }
    saltBuffer[32] = '\0';
}

int main() {
    char hash[65];
    char salt[33];

    for (int i = 0; i < 5; i++) {
        get_salt(salt);
        hash_password("password", salt, hash);
        printf("Test %d: %s\n", i + 1, hash);
    }

    return 0;
}