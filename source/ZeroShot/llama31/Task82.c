#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hashPasswordWithSalt(const char* password, const char* salt, char* output) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, (char*)(password), strlen(password));
    SHA256_Update(&sha256, (char*)(salt), strlen(salt));
    SHA256_Final(hash, &sha256);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + i * 2, "%02x", hash[i]);
    }
}

int main() {
    char passwords[][20] = {"password123", "securepassword", "anotherpassword", "testpassword", "examplepassword"};
    char salts[][20] = {"salt1", "salt2", "salt3", "salt4", "salt5"};
    char hashedPassword[65];

    for (int i = 0; i < 5; i++) {
        hashPasswordWithSalt(passwords[i], salts[i], hashedPassword);
        printf("Password: %s, Salt: %s, Hash: %s\n", passwords[i], salts[i], hashedPassword);
    }

    return 0;
}