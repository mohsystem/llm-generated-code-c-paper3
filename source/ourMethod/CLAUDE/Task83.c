
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* Constants for security requirements */
#define SALT_SIZE 16
#define IV_SIZE 12
#define TAG_SIZE 16
#define KEY_SIZE 32
#define PBKDF2_ITERATIONS 210000
#define MAGIC "ENC1"
#define VERSION 1
#define MAX_PLAINTEXT_SIZE (1024 * 1024)

/* Structure to hold encrypted data */
typedef struct {
    uint8_t* data;
    size_t size;
} encrypted_data_t;

/* Secure memory cleanup - Rules#1: Clear sensitive data */
void secure_zero(void* ptr, size_t len) {
    if (ptr == NULL || len == 0) return;
    volatile uint8_t* p = (volatile uint8_t*)ptr;
    while (len--) *p++ = 0;
}

/* Initialize encrypted_data_t - Rules#1: Initialize all pointers */
void init_encrypted_data(encrypted_data_t* data) {
    if (data != NULL) {
        data->data = NULL;
        data->size = 0;
    }
}

/* Free encrypted_data_t - Rules#1: Free memory exactly once */
void free_encrypted_data(encrypted_data_t* data) {
    if (data != NULL && data->data != NULL) {
        secure_zero(data->data, data->size);
        free(data->data);
        data->data = NULL;
        data->size = 0;
    }
}

/* Derive encryption key using PBKDF2-HMAC-SHA256 - Rules#5, #6, #7, #8 */
int derive_key(const char* passphrase, size_t pass_len,
               const uint8_t* salt, uint8_t* key) {
    if (passphrase == NULL || salt == NULL || key == NULL || pass_len == 0) {
        return 0;
    }
    
    int result = PKCS5_PBKDF2_HMAC(
        passphrase, (int)pass_len,
        salt, SALT_SIZE,
        PBKDF2_ITERATIONS,
        EVP_sha256(),
        KEY_SIZE,
        key
    );
    
    return result;
}

/* Encrypt plaintext using AES-256-GCM - Rules#5, #6 */
int encrypt_aes_gcm(const char* passphrase, size_t pass_len,
                    const uint8_t* plaintext, size_t plaintext_len,
                    encrypted_data_t* output) {
    /* Input validation - Rules#1: Validate all inputs */
    if (passphrase == NULL || plaintext == NULL || output == NULL) {
        return 0;
    }
    if (pass_len == 0 || plaintext_len == 0 || plaintext_len > MAX_PLAINTEXT_SIZE) {
        return 0;
    }
    
    /* Initialize output - Rules#1: Initialize all pointers */
    init_encrypted_data(output);
    
    EVP_CIPHER_CTX* ctx = NULL;
    uint8_t salt[SALT_SIZE];
    uint8_t iv[IV_SIZE];
    uint8_t key[KEY_SIZE];
    uint8_t* ciphertext = NULL;
    uint8_t tag[TAG_SIZE];
    int len = 0;
    int ciphertext_len = 0;
    int success = 0;
    
    /* Initialize all pointers to NULL */
    memset(salt, 0, SALT_SIZE);
    memset(iv, 0, IV_SIZE);
    memset(key, 0, KEY_SIZE);
    memset(tag, 0, TAG_SIZE);
    
    /* Generate cryptographically secure random salt - Rules#7, #8 */
    if (RAND_bytes(salt, SALT_SIZE) != 1) {
        goto cleanup;
    }
    
    /* Generate cryptographically secure random IV - Rules#5, #6 */
    if (RAND_bytes(iv, IV_SIZE) != 1) {
        goto cleanup;
    }
    
    /* Derive encryption key */
    if (!derive_key(passphrase, pass_len, salt, key)) {
        goto cleanup;
    }
    
    /* Create and initialize cipher context - Rules#1: Check all allocations */
    ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        goto cleanup;
    }
    
    /* Initialize encryption with AES-256-GCM - Rules#5, #6 */
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, key, iv) != 1) {
        goto cleanup;
    }
    
    /* Allocate ciphertext buffer - Rules#1: Check malloc return */
    ciphertext = (uint8_t*)malloc(plaintext_len + EVP_CIPHER_block_size(EVP_aes_256_gcm()));
    if (ciphertext == NULL) {
        goto cleanup;
    }
    
    /* Encrypt plaintext - Rules#1: Check all return values */
    if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, (int)plaintext_len) != 1) {
        goto cleanup;
    }
    ciphertext_len = len;
    
    /* Finalize encryption */
    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) {
        goto cleanup;
    }
    ciphertext_len += len;
    
    /* Get authentication tag - Rules#5: 16-byte GCM tag */
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, TAG_SIZE, tag) != 1) {
        goto cleanup;
    }
    
    /* Build output: [magic][version][salt][iv][ciphertext][tag] */
    output->size = 4 + 1 + SALT_SIZE + IV_SIZE + ciphertext_len + TAG_SIZE;
    output->data = (uint8_t*)malloc(output->size);
    if (output->data == NULL) {
        output->size = 0;
        goto cleanup;
    }
    
    /* Copy all components - Rules#1: Bounds-checked operations */
    size_t pos = 0;
    memcpy(output->data + pos, MAGIC, 4);
    pos += 4;
    output->data[pos++] = VERSION;
    memcpy(output->data + pos, salt, SALT_SIZE);
    pos += SALT_SIZE;
    memcpy(output->data + pos, iv, IV_SIZE);
    pos += IV_SIZE;
    memcpy(output->data + pos, ciphertext, ciphertext_len);
    pos += ciphertext_len;
    memcpy(output->data + pos, tag, TAG_SIZE);
    
    success = 1;
    
cleanup:
    /* Securely clear all sensitive data - Rules#1 */
    secure_zero(key, KEY_SIZE);
    secure_zero(salt, SALT_SIZE);
    secure_zero(iv, IV_SIZE);
    secure_zero(tag, TAG_SIZE);
    
    if (ciphertext != NULL) {
        secure_zero(ciphertext, plaintext_len + EVP_CIPHER_block_size(EVP_aes_256_gcm()));
        free(ciphertext);
    }
    
    if (ctx != NULL) {
        EVP_CIPHER_CTX_free(ctx);
    }
    
    if (!success && output->data != NULL) {
        free_encrypted_data(output);
    }
    
    return success;
}

/* Decrypt ciphertext using AES-256-GCM - Rules#5: Verify tag first */
int decrypt_aes_gcm(const char* passphrase, size_t pass_len,
                    const uint8_t* encrypted, size_t encrypted_len,
                    uint8_t** plaintext, size_t* plaintext_len) {
    /* Input validation - Rules#1 */
    if (passphrase == NULL || encrypted == NULL || plaintext == NULL || plaintext_len == NULL) {
        return 0;
    }
    if (pass_len == 0) {
        return 0;
    }
    
    const size_t min_size = 4 + 1 + SALT_SIZE + IV_SIZE + TAG_SIZE;
    if (encrypted_len < min_size) {
        return 0;
    }
    
    /* Initialize output pointers - Rules#1 */
    *plaintext = NULL;
    *plaintext_len = 0;
    
    EVP_CIPHER_CTX* ctx = NULL;
    uint8_t salt[SALT_SIZE];
    uint8_t iv[IV_SIZE];
    uint8_t key[KEY_SIZE];
    uint8_t tag[TAG_SIZE];
    uint8_t* ciphertext = NULL;
    size_t ciphertext_len = 0;
    int len = 0;
    int success = 0;
    
    /* Initialize arrays */
    memset(salt, 0, SALT_SIZE);
    memset(iv, 0, IV_SIZE);
    memset(key, 0, KEY_SIZE);
    memset(tag, 0, TAG_SIZE);
    
    /* Parse encrypted data */
    size_t pos = 0;
    
    /* Verify magic - Rules#1: Validate format */
    if (memcmp(encrypted + pos, MAGIC, 4) != 0) {
        goto cleanup;
    }
    pos += 4;
    
    /* Verify version */
    if (encrypted[pos] != VERSION) {
        goto cleanup;
    }
    pos += 1;
    
    /* Extract salt */
    memcpy(salt, encrypted + pos, SALT_SIZE);
    pos += SALT_SIZE;
    
    /* Extract IV */
    memcpy(iv, encrypted + pos, IV_SIZE);
    pos += IV_SIZE;
    
    /* Calculate ciphertext length */
    ciphertext_len = encrypted_len - pos - TAG_SIZE;
    
    /* Extract ciphertext - Rules#1: Check allocation */
    ciphertext = (uint8_t*)malloc(ciphertext_len);
    if (ciphertext == NULL) {
        goto cleanup;
    }
    memcpy(ciphertext, encrypted + pos, ciphertext_len);
    pos += ciphertext_len;
    
    /* Extract tag */
    memcpy(tag, encrypted + pos, TAG_SIZE);
    
    /* Derive decryption key */
    if (!derive_key(passphrase, pass_len, salt, key)) {
        goto cleanup;
    }
    
    /* Create cipher context */
    ctx = EVP_CIPHER_CTX_new();
    if (ctx == NULL) {
        goto cleanup;
    }
    
    /* Initialize decryption */
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, key, iv) != 1) {
        goto cleanup;
    }
    
    /* Allocate plaintext buffer */
    *plaintext = (uint8_t*)malloc(ciphertext_len + EVP_CIPHER_block_size(EVP_aes_256_gcm()));
    if (*plaintext == NULL) {
        goto cleanup;
    }
    
    /* Decrypt ciphertext */
    if (EVP_DecryptUpdate(ctx, *plaintext, &len, ciphertext, (int)ciphertext_len) != 1) {
        goto cleanup;
    }
    *plaintext_len = len;
    
    /* Set expected tag value - Rules#5: Verify tag */
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, TAG_SIZE, tag) != 1) {
        goto cleanup;
    }
    
    /* Finalize decryption - tag verification happens here */
    int ret = EVP_DecryptFinal_ex(ctx, *plaintext + len, &len);
    if (ret <= 0) {
        /* Tag verification failed - Rules#5: Fail closed */
        secure_zero(*plaintext, *plaintext_len);
        free(*plaintext);
        *plaintext = NULL;
        *plaintext_len = 0;
        goto cleanup;
    }
    *plaintext_len += len;
    
    success = 1;
    
cleanup:
    /* Securely clear all sensitive data */
    secure_zero(key, KEY_SIZE);
    secure_zero(salt, SALT_SIZE);
    secure_zero(iv, IV_SIZE);
    secure_zero(tag, TAG_SIZE);
    
    if (ciphertext != NULL) {
        secure_zero(ciphertext, ciphertext_len);
        free(ciphertext);
    }
    
    if (ctx != NULL) {
        EVP_CIPHER_CTX_free(ctx);
    }
    
    return success;
}

/* Test runner */
int main(void) {
    printf("AES-256-GCM Encryption Test Cases (C)\n");
    printf("======================================\n\n");
    
    /* Test case 1: Basic encryption/decryption */
    printf("Test 1: Basic encryption and decryption\n");
    {
        const char* passphrase = "SecurePassphrase123!@#";
        const uint8_t plaintext[] = "Hello World!";
        size_t plaintext_len = sizeof(plaintext) - 1;
        
        encrypted_data_t encrypted;
        init_encrypted_data(&encrypted);
        
        if (encrypt_aes_gcm(passphrase, strlen(passphrase), plaintext, plaintext_len, &encrypted)) {
            printf("  Encrypted size: %zu bytes\n", encrypted.size);
            
            uint8_t* decrypted = NULL;
            size_t decrypted_len = 0;
            
            if (decrypt_aes_gcm(passphrase, strlen(passphrase), encrypted.data, encrypted.size, 
                               &decrypted, &decrypted_len)) {
                printf("  Decrypted: %.*s\n", (int)decrypted_len, decrypted);
                int match = (decrypted_len == plaintext_len && 
                           memcmp(decrypted, plaintext, plaintext_len) == 0);
                printf("  Status: %s\n\n", match ? "PASS" : "FAIL");
                secure_zero(decrypted, decrypted_len);
                free(decrypted);
            } else {
                printf("  Decryption failed\n\n");
            }
            
            free_encrypted_data(&encrypted);
        } else {
            printf("  Encryption failed\n\n");
        }
    }
    
    /* Test case 2: Different passphrase produces different ciphertext */
    printf("Test 2: Different passphrase produces different ciphertext\n");
    {
        const uint8_t plaintext[] = "Test Data";
        size_t plaintext_len = sizeof(plaintext) - 1;
        
        encrypted_data_t enc1, enc2;
        init_encrypted_data(&enc1);
        init_encrypted_data(&enc2);
        
        int success1 = encrypt_aes_gcm("password1", 9, plaintext, plaintext_len, &enc1);
        int success2 = encrypt_aes_gcm("password2", 9, plaintext, plaintext_len, &enc2);
        
        if (success1 && success2) {
            int different = (enc1.size != enc2.size || 
                           memcmp(enc1.data, enc2.data, enc1.size) != 0);
            printf("  Ciphertext 1 != Ciphertext 2: %s\n\n", different ? "PASS" : "FAIL");
        } else {
            printf("  Encryption failed\n\n");
        }
        
        free_encrypted_data(&enc1);
        free_encrypted_data(&enc2);
    }
    
    /* Test case 3: Wrong passphrase fails decryption */
    printf("Test 3: Wrong passphrase fails authentication\n");
    {
        const uint8_t plaintext[] = "Secret";
        size_t plaintext_len = sizeof(plaintext) - 1;
        
        encrypted_data_t encrypted;
        init_encrypted_data(&encrypted);
        
        if (encrypt_aes_gcm("correct_password", 16, plaintext, plaintext_len, &encrypted)) {
            uint8_t* decrypted = NULL;
            size_t decrypted_len = 0;
            
            int result = decrypt_aes_gcm("wrong_password", 14, encrypted.data, encrypted.size,
                                        &decrypted, &decrypted_len);
            
            if (!result) {
                printf("  Status: PASS (correctly rejected wrong passphrase)\n\n");
            } else {
                printf("  Status: FAIL (should have rejected wrong passphrase)\\n\\n");
                if (decrypted != NULL) {
                    secure_zero(decrypted, decrypted_len);
                    free(decrypted);
                }
            }
            
            free_encrypted_data(&encrypted);
        } else {
            printf("  Encryption failed\\n\\n");
        }
    }
    
    /* Test case 4: Tampering detection */
    printf("Test 4: Tampered ciphertext is rejected\\n");
    {
        const uint8_t plaintext[] = "Data";
        size_t plaintext_len = sizeof(plaintext) - 1;
        
        encrypted_data_t encrypted;
        init_encrypted_data(&encrypted);
        
        if (encrypt_aes_gcm("password", 8, plaintext, plaintext_len, &encrypted)) {
            /* Tamper with ciphertext */
            if (encrypted.size > 50) {
                encrypted.data[50] ^= 0xFF;
            }
            
            uint8_t* decrypted = NULL;
            size_t decrypted_len = 0;
            
            int result = decrypt_aes_gcm("password", 8, encrypted.data, encrypted.size,
                                        &decrypted, &decrypted_len);
            
            if (!result) {
                printf("  Status: PASS (correctly detected tampering)\\n\\n");
            } else {
                printf("  Status: FAIL (should have detected tampering)\\n\\n");
                if (decrypted != NULL) {
                    secure_zero(decrypted, decrypted_len);
                    free(decrypted);
                }
            }
            
            free_encrypted_data(&encrypted);
        } else {
            printf("  Encryption failed\\n\\n");
        }
    }
    
    /* Test case 5: Larger data encryption */
    printf("Test 5: Larger data encryption\\n");
    {
        const size_t size = 1000;
        uint8_t* plaintext = (uint8_t*)malloc(size);
        if (plaintext != NULL) {
            for (size_t i = 0; i < size; i++) {
                plaintext[i] = (uint8_t)('A' + (i % 26));
            }
            
            encrypted_data_t encrypted;
            init_encrypted_data(&encrypted);
            
            if (encrypt_aes_gcm("LongPassword!@#$", 16, plaintext, size, &encrypted)) {
                uint8_t* decrypted = NULL;
                size_t decrypted_len = 0;
                
                if (decrypt_aes_gcm("LongPassword!@#$", 16, encrypted.data, encrypted.size,
                                   &decrypted, &decrypted_len)) {
                    printf("  Original size: %zu bytes\\n", size);
                    printf("  Encrypted size: %zu bytes\\n", encrypted.size);
                    printf("  Decrypted size: %zu bytes\\n", decrypted_len);
                    
                    int match = (decrypted_len == size && memcmp(decrypted, plaintext, size) == 0);
                    printf("  Status: %s\\n\\n", match ? "PASS" : "FAIL");
                    
                    secure_zero(decrypted, decrypted_len);
                    free(decrypted);
                } else {
                    printf("  Decryption failed\\n\\n");
                }
                
                free_encrypted_data(&encrypted);
            } else {
                printf("  Encryption failed\\n\\n");
            }
            
            secure_zero(plaintext, size);
            free(plaintext);
        }
    }
    
    return 0;
}
