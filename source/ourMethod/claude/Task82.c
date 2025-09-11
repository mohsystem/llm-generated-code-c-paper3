
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define SALT_LENGTH 32  // 256 bits
#define SHA256_LENGTH 32  // SHA-256 produces 256 bit (32 byte) hashes

// Returns dynamically allocated string that must be freed by caller
// Returns NULL on error
char* hash_password(const char* password) {
    if(!password) return NULL;
    
    // Generate random salt
    unsigned char salt[SALT_LENGTH];
    if(RAND_bytes(salt, SALT_LENGTH) != 1) {
        return NULL;
    }
    
    // Hash password with salt
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    
    unsigned char hash[SHA256_LENGTH];
    SHA256_Final(hash, &sha256);
    
    // Combine salt and hash
    unsigned char* salt_and_hash = malloc(SALT_LENGTH + SHA256_LENGTH);
    if(!salt_and_hash) return NULL;
    
    memcpy(salt_and_hash, salt, SALT_LENGTH);
    memcpy(salt_and_hash + SALT_LENGTH, hash, SHA256_LENGTH);
    
    // Convert to base64
    static const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t b64len = ((SALT_LENGTH + SHA256_LENGTH + 2) / 3) * 4 + 1;
    char* b64 = malloc(b64len);
    if(!b64) {
        free(salt_and_hash);
        return NULL;
    }
    
    int i = 0, j = 0;
    int len = SALT_LENGTH + SHA256_LENGTH;
    
    while (i < len) {
        unsigned char b1 = (i < len) ? salt_and_hash[i++] : 0;
        unsigned char b2 = (i < len) ? salt_and_hash[i++] : 0;
        unsigned char b3 = (i < len) ? salt_and_hash[i++] : 0;
        
        b64[j++] = b64chars[(b1 & 0xfc) >> 2];
        b64[j++] = b64chars[((b1 & 0x03) << 4) + ((b2 & 0xf0) >> 4)];
        b64[j++] = (i > len+1) ? '=' : b64chars[((b2 & 0x0f) << 2) + ((b3 & 0xc0) >> 6)];
        b64[j++] = (i > len) ? '=' : b64chars[b3 & 0x3f];
    }
    b64[j] = '\\0';
    
    free(salt_and_hash);
    return b64;
}

int main() {
    // Test cases
    char* hash;
    
    hash = hash_password("password123");
    printf("Hash 1: %s\\n", hash ? hash : "ERROR");
    free(hash);
    
    hash = hash_password("password123"); // Different salt = different hash
    printf("Hash 2: %s\\n", hash ? hash : "ERROR");
    free(hash);
    
    hash = hash_password("Password123");
    printf("Hash 3: %s\\n", hash ? hash : "ERROR");
    free(hash);
    
    hash = hash_password("");
    printf("Hash 4: %s\\n", hash ? hash : "ERROR");
    free(hash);
    
    hash = hash_password("verylongpasswordthatisverylongindeed");
    printf("Hash 5: %s\\n", hash ? hash : "ERROR");
    free(hash);
    
    return 0;
}
