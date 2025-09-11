#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

char* getSaltedPasswordHash(const char* password, const char* salt) {
    char saltedPassword[256]; // Adjust size as needed
    strcpy(saltedPassword, salt);
    strcat(saltedPassword, password);
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, saltedPassword, strlen(saltedPassword));
    SHA256_Final(hash, &sha256);
    char* output = (char*) malloc(sizeof(char) * (SHA256_DIGEST_LENGTH * 2 + 1));
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + i * 2, "%02x", hash[i]);
    }
    return output;
}

int main() {
    char* hash1 = getSaltedPasswordHash("password123", "salt1");
    printf("%s\n", hash1);
    free(hash1);
    char* hash2 = getSaltedPasswordHash("test", "salt2");
    printf("%s\n", hash2);
    free(hash2);
    char* hash3 = getSaltedPasswordHash("123456", "salt3");
    printf("%s\n", hash3);
    free(hash3);
    char* hash4 = getSaltedPasswordHash("qwerty", "salt4");
    printf("%s\n", hash4);
    free(hash4);
    char* hash5 = getSaltedPasswordHash("password", "salt5");
    printf("%s\n", hash5);
    free(hash5);
    return 0;
}