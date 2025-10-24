
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/crypto.h>

#define SALT_SIZE 16
#define HASH_SIZE 32
#define ITERATIONS 210000
#define HEX_HASH_SIZE 96  // 32 hex salt + 64 hex hash
// Securely generates cryptographically random salt - CWE-330, CWE-338, CWE-759
int generate_salt(uint8_t *salt, size_t salt_size) {
    // Validate input pointer - CWE-476: NULL Pointer Dereference
    if (salt == NULL || salt_size != SALT_SIZE) {
        return 0;
    }

    // Use OpenSSL's cryptographically secure RNG
    int result = RAND_bytes(salt, (int)salt_size);
    if (result != 1) {
        return 0;
    }

    return 1;
}

// Computes PBKDF2-HMAC-SHA256 hash with salt - CWE-326, CWE-916
int hash_password_with_salt(const char *password, size_t password_len,
                            const uint8_t *salt, size_t salt_size,
                            char *output_hex, size_t output_size) {
    // Validate all inputs - CWE-20: Improper Input Validation
    if (password == NULL || salt == NULL || output_hex == NULL) {
        return 0;
    }

    if (password_len == 0 || password_len > 1024) {
        return 0;
    }

    if (salt_size != SALT_SIZE) {
        return 0;
    }

    if (output_size < HEX_HASH_SIZE + 1) {
        return 0;
    }

    uint8_t hash[HASH_SIZE];
    memset(hash, 0, HASH_SIZE);

    // Derive key using PBKDF2-HMAC-SHA256 with 210000 iterations
    int result = PKCS5_PBKDF2_HMAC(
        password,
        (int)password_len,
        salt,
        (int)salt_size,
        ITERATIONS,
        EVP_sha256(),
        HASH_SIZE,
        hash
    );

    if (result != 1) {
        OPENSSL_cleanse(hash, HASH_SIZE);
        return 0;
    }

    // Convert salt and hash to hex string - CWE-134: Use of Externally-Controlled Format String
    size_t pos = 0;

    // Append salt (16 bytes = 32 hex chars)
    for (size_t i = 0; i < salt_size && pos < output_size - 1; i++) {
        int written = snprintf(output_hex + pos, output_size - pos, "%02x", salt[i]);
        if (written < 0 || written >= (int)(output_size - pos)) {
            OPENSSL_cleanse(hash, HASH_SIZE);
            return 0;
        }
        pos += (size_t)written;
    }

    // Append hash (32 bytes = 64 hex chars)
    for (size_t i = 0; i < HASH_SIZE && pos < output_size - 1; i++) {
        int written = snprintf(output_hex + pos, output_size - pos, "%02x", hash[i]);
        if (written < 0 || written >= (int)(output_size - pos)) {
            OPENSSL_cleanse(hash, HASH_SIZE);
            return 0;
        }
        pos += (size_t)written;
    }

    output_hex[pos] = '\0';

    // Securely clear sensitive data - CWE-244: Improper Clearing of Heap Memory
    OPENSSL_cleanse(hash, HASH_SIZE);

    return 1;
}

// Verify password against stored hash with constant-time comparison
int verify_password(const char *password, size_t password_len, const char *stored_hash) {
    // Validate inputs
    if (password == NULL || stored_hash == NULL) {
        return 0;
    }

    size_t stored_len = strlen(stored_hash);
    if (stored_len != HEX_HASH_SIZE) {
        return 0;
    }

    // Extract salt from stored hash (first 32 hex chars)
    uint8_t salt[SALT_SIZE];
    for (size_t i = 0; i < SALT_SIZE; i++) {
        char byte_str[3] = {stored_hash[i * 2], stored_hash[i * 2 + 1], '\0'};
        unsigned int byte_val;
        if (sscanf(byte_str, "%02x", &byte_val) != 1) {
            return 0;
        }
        salt[i] = (uint8_t)byte_val;
    }

    // Compute hash with extracted salt
    char computed_hash[HEX_HASH_SIZE + 1];
    if (!hash_password_with_salt(password, password_len, salt, SALT_SIZE,
                                 computed_hash, sizeof(computed_hash))) {
        return 0;
    }

    // Constant-time comparison - CWE-208: Observable Timing Discrepancy
    int matches = 1;
    for (size_t i = 0; i < HEX_HASH_SIZE; i++) {
        matches &= (computed_hash[i] == stored_hash[i]);
    }

    // Securely clear computed hash
    OPENSSL_cleanse(computed_hash, sizeof(computed_hash));

    return matches;
}


int main(void) {
    printf("Password Hashing with Salt - Test Suite\n");
    printf("========================================\n\n");
    
    // Test case 1: Basic password hashing
    printf("Test 1: Hash password with generated salt\n");
    const char *password1 = "SecurePassword123!";
    uint8_t salt1[SALT_SIZE];
    char hash1[HEX_HASH_SIZE + 1];
    
    if (!generate_salt(salt1, SALT_SIZE)) {
        fprintf(stderr, "Failed to generate salt\n");
        return 1;
    }
    
    if (!hash_password_with_salt(password1, strlen(password1), salt1, SALT_SIZE, 
                                  hash1, sizeof(hash1))) {
        fprintf(stderr, "Failed to hash password\n");
        return 1;
    }
    
    printf("Hash (salt+hash): %.40s...\n", hash1);
    printf("Length: %zu chars (32 salt + 64 hash)\n\n", strlen(hash1));
    
    // Test case 2: Verify correct password
    printf("Test 2: Verify correct password\n");
    int valid = verify_password(password1, strlen(password1), hash1);
    printf("Verification result: %s\n\n", valid ? "PASS" : "FAIL");
    
    // Test case 3: Verify wrong password
    printf("Test 3: Verify incorrect password\n");
    const char *wrong_password = "WrongPassword";
    int invalid = verify_password(wrong_password, strlen(wrong_password), hash1);
    printf("Verification result: %s (correctly rejected)\n\n",
           invalid ? "FAIL" : "PASS");
    
    // Test case 4: Same password, different salt
    printf("Test 4: Same password with different salt\n");
    uint8_t salt2[SALT_SIZE];
    char hash2[HEX_HASH_SIZE + 1];
    
    if (!generate_salt(salt2, SALT_SIZE)) {
        fprintf(stderr, "Failed to generate salt\n");
        return 1;
    }
    
    if (!hash_password_with_salt(password1, strlen(password1), salt2, SALT_SIZE,
                                  hash2, sizeof(hash2))) {
        fprintf(stderr, "Failed to hash password\n");
        return 1;
    }
    
    printf("Hash 1: %.40s...\n", hash1);
    printf("Hash 2: %.40s...\n", hash2);
    printf("Hashes different: %s\n\n", strcmp(hash1, hash2) != 0 ? "PASS" : "FAIL");
    
    // Test case 5: Complex password
    printf("Test 5: Complex password with special characters\n");
    const char *password3 = "P@ssw0rd!#$%%^&*()_+";
    uint8_t salt3[SALT_SIZE];
    char hash3[HEX_HASH_SIZE + 1];
    
    if (!generate_salt(salt3, SALT_SIZE)) {
        fprintf(stderr, "Failed to generate salt\n");
        return 1;
    }
    
    if (!hash_password_with_salt(password3, strlen(password3), salt3, SALT_SIZE,
                                  hash3, sizeof(hash3))) {
        fprintf(stderr, "Failed to hash password\n");
        return 1;
    }
    
    int valid3 = verify_password(password3, strlen(password3), hash3);
    printf("Hash computed and verified: %s\n", valid3 ? "PASS" : "FAIL");
    
    // Securely clear sensitive data before exit
    OPENSSL_cleanse(salt1, SALT_SIZE);
    OPENSSL_cleanse(salt2, SALT_SIZE);
    OPENSSL_cleanse(salt3, SALT_SIZE);
    OPENSSL_cleanse(hash1, sizeof(hash1));
    OPENSSL_cleanse(hash2, sizeof(hash2));
    OPENSSL_cleanse(hash3, sizeof(hash3));
    
    return 0;
}
