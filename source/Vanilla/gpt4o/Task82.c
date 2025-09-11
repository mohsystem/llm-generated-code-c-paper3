#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPasswordWithSalt(const char* password, const char* salt, char* outputBuffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char saltedPassword[256];
    snprintf(saltedPassword, sizeof(saltedPassword), "%s%s", salt, password);
    SHA256((unsigned char*)saltedPassword, strlen(saltedPassword), hash);
    
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    }
}

int main() {
    char outputBuffer[65]; // 64 chars for SHA256 and 1 for null terminator

    hashPasswordWithSalt("password123", "salt1", outputBuffer);
    printf("%s\n", outputBuffer); // Test case 1

    hashPasswordWithSalt("helloWorld", "salt2", outputBuffer);
    printf("%s\n", outputBuffer); // Test case 2

    hashPasswordWithSalt("javaCode", "salt3", outputBuffer);
    printf("%s\n", outputBuffer); // Test case 3

    hashPasswordWithSalt("securePassword", "salt4", outputBuffer);
    printf("%s\n", outputBuffer); // Test case 4

    hashPasswordWithSalt("hashThis", "salt5", outputBuffer);
    printf("%s\n", outputBuffer); // Test case 5

    return 0;
}