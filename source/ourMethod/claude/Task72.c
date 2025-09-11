
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define BLOCK_SIZE 16

typedef struct {
    unsigned char iv[BLOCK_SIZE];
} Task72;

// Generate static IV
static void generate_static_iv(unsigned char *iv) {
    if (RAND_bytes(iv, BLOCK_SIZE) != 1) {
        fprintf(stderr, "Failed to generate IV\\n");
        exit(1);
    }
}

// Encrypt data using AES-CBC
static unsigned char* encrypt(Task72 *t, const unsigned char *data, size_t data_len, 
                            const unsigned char *key, size_t key_len, size_t *out_len) {
    // Input validation
    if (!data || !key || !data_len) {
        return NULL;
    }
    if (key_len != 16 && key_len != 24 && key_len != 32) {
        return NULL;
    }

    // Calculate padded length
    size_t padded_len = ((data_len + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    *out_len = padded_len;

    // Allocate memory for padded data
    unsigned char *padded_data = (unsigned char*)malloc(padded_len);
    if (!padded_data) {
        return NULL;
    }

    // Copy input data and add PKCS7 padding
    memcpy(padded_data, data, data_len);
    unsigned char pad_value = padded_len - data_len;
    memset(padded_data + data_len, pad_value, pad_value);

    // Initialize AES key
    AES_KEY aes_key;
    if (AES_set_encrypt_key(key, key_len * 8, &aes_key) < 0) {
        free(padded_data);
        return NULL;
    }

    // Allocate memory for encrypted data
    unsigned char *encrypted = (unsigned char*)malloc(padded_len);
    if (!encrypted) {
        free(padded_data);
        return NULL;
    }

    // Create copy of IV since it gets modified during encryption
    unsigned char iv_copy[BLOCK_SIZE];
    memcpy(iv_copy, t->iv, BLOCK_SIZE);

    // Perform encryption
    AES_cbc_encrypt(padded_data, encrypted, padded_len, &aes_key, iv_copy, AES_ENCRYPT);

    free(padded_data);
    return encrypted;
}

int main() {
    Task72 task;
    generate_static_iv(task.iv);

    // Test cases
    unsigned char key16[16];
    memset(key16, 1, sizeof(key16));

    // Test 1: Basic encryption
    const char *test1 = "Hello World";
    size_t encrypted_len;
    unsigned char *encrypted = encrypt(&task, (unsigned char*)test1, strlen(test1), 
                                     key16, sizeof(key16), &encrypted_len);
    if (encrypted) {
        printf("Test 1 successful\\n");
        free(encrypted);
    }

    // Test 2: Empty input
    encrypted = encrypt(&task, (unsigned char*)"", 0, key16, sizeof(key16), &encrypted_len);
    if (!encrypted) {
        printf("Test 2 successful (expected NULL for empty input)\\n");
    }

    // Test 3: Long string
    const char *test3 = "This is a much longer string that will require multiple blocks";
    encrypted = encrypt(&task, (unsigned char*)test3, strlen(test3), 
                       key16, sizeof(key16), &encrypted_len);
    if (encrypted) {
        printf("Test 3 successful\\n");
        free(encrypted);
    }

    // Test 4: Binary data
    unsigned char test4[] = {1, 2, 3, 4, 5};
    encrypted = encrypt(&task, test4, sizeof(test4), key16, sizeof(key16), &encrypted_len);
    if (encrypted) {
        printf("Test 4 successful\\n");
        free(encrypted);
    }

    // Test 5: 32-byte key
    unsigned char key32[32];
    memset(key32, 2, sizeof(key32));
    const char *test5 = "Testing with 256-bit key";
    encrypted = encrypt(&task, (unsigned char*)test5, strlen(test5), 
                       key32, sizeof(key32), &encrypted_len);
    if (encrypted) {
        printf("Test 5 successful\\n");
        free(encrypted);
    }

    return 0;
}
