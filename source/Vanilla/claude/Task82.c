
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

void hash_password(const char* password, const char* salt, char* output) {
    SHA256_CTX sha256;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char combined[256];
    
    snprintf(combined, sizeof(combined), "%s%s", password, salt);
    
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, combined, strlen(combined));
    SHA256_Final(hash, &sha256);
    
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }
    output[SHA256_DIGEST_LENGTH * 2] = 0;
}

int main() {
    char hashed[65];  // 32 bytes * 2 for hex representation + 1 for null terminator
    
    // Test cases
    hash_password("password123", "salt123", hashed);
    printf("%s\\n", hashed);
    
    hash_password("abc123", "randomsalt", hashed);
    printf("%s\\n", hashed);
    
    hash_password("securepass", "pepper", hashed);
    printf("%s\\n", hashed);
    
    hash_password("test1234", "sodium", hashed);
    printf("%s\\n", hashed);
    
    hash_password("mypassword", "sugar", hashed);
    printf("%s\\n", hashed);
    
    return 0;
}
