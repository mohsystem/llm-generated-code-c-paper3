
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#define SALT_SIZE 16
#define KEY_SIZE 32
#define IV_SIZE 16
#define ITERATION_COUNT 65536

typedef struct {
    unsigned char* data;
    size_t length;
} encrypted_data;

encrypted_data* encrypt(const char* input, const char* password) {
    if (input == NULL || password == NULL) {
        return NULL;
    }

    // Allocate result structure
    encrypted_data* result = malloc(sizeof(encrypted_data));
    if (!result) {
        return NULL;
    }

    // Generate salt
    unsigned char salt[SALT_SIZE];
    if (RAND_bytes(salt, SALT_SIZE) != 1) {
        free(result);
        return NULL;
    }

    // Generate key using PBKDF2
    unsigned char key[KEY_SIZE];
    if (PKCS5_PBKDF2_HMAC(password, strlen(password),
                          salt, SALT_SIZE,
                          ITERATION_COUNT,
                          EVP_sha256(),
                          KEY_SIZE, key) != 1) {
        free(result);
        return NULL;
    }

    // Generate IV
    unsigned char iv[IV_SIZE];
    if (RAND_bytes(iv, IV_SIZE) != 1) {
        free(result);
        return NULL;
    }

    // Create and initialize the context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        free(result);
        return NULL;
    }

    // Initialize encryption operation
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(result);
        return NULL;
    }

    size_t input_len = strlen(input);
    size_t max_ciphertext_len = input_len + EVP_MAX_BLOCK_LENGTH;
    unsigned char* ciphertext = malloc(max_ciphertext_len);
    if (!ciphertext) {
        EVP_CIPHER_CTX_free(ctx);
        free(result);
        return NULL;
    }

    int len1, len2;

    // Encrypt the input
    if (EVP_EncryptUpdate(ctx, ciphertext, &len1,
                         (unsigned char*)input, input_len) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(ciphertext);
        free(result);
        return NULL;
    }

    // Finalize encryption
    if (EVP_EncryptFinal_ex(ctx, ciphertext + len1, &len2) != 1) {
        EVP_CIPHER_CTX_free(ctx);
        free(ciphertext);
        free(result);
        return NULL;
    }

    EVP_CIPHER_CTX_free(ctx);

    // Allocate final result buffer
    size_t total_len = SALT_SIZE + IV_SIZE + len1 + len2;
    result->data = malloc(total_len);
    if (!result->data) {
        free(ciphertext);
        free(result);
        return NULL;
    }
    result->length = total_len;

    // Combine salt, IV, and ciphertext
    memcpy(result->data, salt, SALT_SIZE);
    memcpy(result->data + SALT_SIZE, iv, IV_SIZE);
    memcpy(result->data + SALT_SIZE + IV_SIZE, ciphertext, len1 + len2);

    free(ciphertext);
    return result;
}

void free_encrypted_data(encrypted_data* data) {
    if (data) {
        if (data->data) {
            free(data->data);
        }
        free(data);
    }
}

int main() {
    // Initialize OpenSSL
    OpenSSL_add_all_algorithms();

    // Test cases
    const char* inputs[] = {
        "Hello World!",
        "Sensitive Data 123",
        "Test@#$%^&*()",
        "Very Long String That Needs To Be Encrypted Securely",
        ""  // Empty string test
    };
    const char* password = "SecurePassword123!";
    int num_tests = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_tests; i++) {
        printf("Input: %s\\n", inputs[i]);
        encrypted_data* encrypted = encrypt(inputs[i], password);
        
        if (encrypted) {
            printf("Encrypted (hex): ");
            for (size_t j = 0; j < encrypted->length; j++) {
                printf("%02x", encrypted->data[j]);
            }
            printf("\\n\\n");
            
            free_encrypted_data(encrypted);
        } else {
            printf("Encryption failed\\n\\n");
        }
    }

    EVP_cleanup();
    return 0;
}
