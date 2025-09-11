
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define SALT_LENGTH 16
#define SHA256_LENGTH 32

void generate_salt(unsigned char *salt, size_t length) {
    RAND_bytes(salt, length);
}

void hash_password(const char *password, const unsigned char *salt, 
                  size_t salt_length, unsigned char *output) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salt, salt_length);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

void bytes_to_hex(const unsigned char *data, size_t len, char *output) {
    for(size_t i = 0; i < len; i++) {
        sprintf(output + (i * 2), "%02x", data[i]);
    }
}

int main() {
    const char *passwords[] = {
        "password123",
        "SecurePass!@#",
        "TestPass987",
        "ComplexP@ssw0rd",
        "SimpleP@ss"
    };
    
    unsigned char salt[SALT_LENGTH];
    unsigned char hashed[SHA256_LENGTH];
    char hex_salt[SALT_LENGTH * 2 + 1];
    char hex_hash[SHA256_LENGTH * 2 + 1];
    
    for(int i = 0; i < 5; i++) {
        // Generate salt
        generate_salt(salt, SALT_LENGTH);
        
        // Hash password with salt
        hash_password(passwords[i], salt, SALT_LENGTH, hashed);
        
        // Convert to hex strings
        bytes_to_hex(salt, SALT_LENGTH, hex_salt);
        bytes_to_hex(hashed, SHA256_LENGTH, hex_hash);
        hex_salt[SALT_LENGTH * 2] = '\\0';
        hex_hash[SHA256_LENGTH * 2] = '\\0';
        
        printf("Password: %s\\n", passwords[i]);
        printf("Salt (Hex): %s\\n", hex_salt);
        printf("Hashed Password: %s\\n\\n", hex_hash);
    }
    
    return 0;
}
