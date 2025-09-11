#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPasswordWithSalt(const char* password, const char* salt, char* outputBuffer) {
    char combined[1024];
    snprintf(combined, sizeof(combined), "%s%s", password, salt);

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)combined, strlen(combined), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    char hashOutput[65];
    hashPasswordWithSalt("password1", "salt1", hashOutput);
    printf("%s\n", hashOutput);

    hashPasswordWithSalt("password2", "salt2", hashOutput);
    printf("%s\n", hashOutput);

    hashPasswordWithSalt("password3", "salt3", hashOutput);
    printf("%s\n", hashOutput);

    hashPasswordWithSalt("password4", "salt4", hashOutput);
    printf("%s\n", hashOutput);

    hashPasswordWithSalt("password5", "salt5", hashOutput);
    printf("%s\n", hashOutput);

    return 0;
}