#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

// Constants
#define SALT_LENGTH_BYTES 16
#define IV_LENGTH_BYTES 12
#define TAG_LENGTH_BYTES 16
#define KEY_LENGTH_BYTES 32 // 256 bits
#define PBKDF2_ITERATIONS 600000
const char* MAGIC_BYTES = "ENC1";
const unsigned char VERSION = 0x01;


// Returns base64 encoded string, caller must free it. Returns NULL on failure.
char* base64_encode(const unsigned char* input, int length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;
    char *b64text;

    b64 = BIO_new(BIO_f_base64());
    if (!b64) return NULL;
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new(BIO_s_mem());
    if (!bio) { BIO_free_all(b64); return NULL; }
    bio = BIO_push(b64, bio);

    if (BIO_write(bio, input, length) <= 0) {
        BIO_free_all(bio);
        return NULL;
    }
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    
    b64text = (char*)malloc(bufferPtr->length + 1);
    if (!b64text) { BIO_free_all(bio); return NULL; }
    memcpy(b64text, bufferPtr->data, bufferPtr->length);
    b64text[bufferPtr->length] = 0;

    BIO_free_all(bio);
    return b64text;
}

// Returns decoded data, caller must free it. Writes length to out_len. Returns NULL on failure.
unsigned char* base64_decode(const char* input, int* out_len) {
    BIO *bio, *b64;
    int input_len = strlen(input);
    unsigned char* buffer = (unsigned char*)malloc(input_len);
    if (!buffer) return NULL;

    b64 = BIO_new(BIO_f_base64());
    if (!b64) { free(buffer); return NULL; }
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bio = BIO_new_mem_buf(input, input_len);
    if (!bio) { BIO_free_all(b64); free(buffer); return NULL; }
    bio = BIO_push(b64, bio);

    *out_len = BIO_read(bio, buffer, input_len);
    BIO_free_all(bio);

    if (*out_len < 0) {
        free(buffer);
        return NULL;
    }
    return buffer;
}


int encrypt_string(const char* plaintext, const char* password, char** base64_ciphertext) {
    int status = -1;
    unsigned char salt[SALT_LENGTH_BYTES];
    unsigned char key[KEY_LENGTH_BYTES];
    unsigned char iv[IV_LENGTH_BYTES];
    unsigned char *ciphertext = NULL;
    unsigned char tag[TAG_LENGTH_BYTES];
    unsigned char *output = NULL;
    EVP_CIPHER_CTX *ctx = NULL;
    int len, ciphertext_len = 0;

    if (RAND_bytes(salt, sizeof(salt)) != 1) goto cleanup;
    if (PKCS5_PBKDF2_HMAC(password, strlen(password), salt, sizeof(salt), PBKDF2_ITERATIONS, EVP_sha256(), sizeof(key), key) != 1) goto cleanup;
    if (RAND_bytes(iv, sizeof(iv)) != 1) goto cleanup;
    
    if (!(ctx = EVP_CIPHER_CTX_new())) goto cleanup;
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL)) goto cleanup;
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, sizeof(iv), NULL)) goto cleanup;
    if (1 != EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv)) goto cleanup;
    
    ciphertext = malloc(strlen(plaintext) + EVP_CIPHER_block_size(EVP_aes_256_gcm()));
    if (!ciphertext) goto cleanup;

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (const unsigned char*)plaintext, strlen(plaintext))) goto cleanup;
    ciphertext_len = len;
    
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) goto cleanup;
    ciphertext_len += len;
    
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, sizeof(tag), tag)) goto cleanup;

    size_t output_len = strlen(MAGIC_BYTES) + 1 + sizeof(salt) + sizeof(iv) + ciphertext_len + sizeof(tag);
    output = malloc(output_len);
    if (!output) goto cleanup;

    unsigned char* p = output;
    memcpy(p, MAGIC_BYTES, strlen(MAGIC_BYTES)); p += strlen(MAGIC_BYTES);
    *p = VERSION; p++;
    memcpy(p, salt, sizeof(salt)); p += sizeof(salt);
    memcpy(p, iv, sizeof(iv)); p += sizeof(iv);
    memcpy(p, ciphertext, ciphertext_len); p += ciphertext_len;
    memcpy(p, tag, sizeof(tag));

    *base64_ciphertext = base64_encode(output, output_len);
    if (!*base64_ciphertext) goto cleanup;

    status = 0; // Success

cleanup:
    if (ctx) EVP_CIPHER_CTX_free(ctx);
    if (ciphertext) free(ciphertext);
    if (output) free(output);
    OPENSSL_cleanse(key, sizeof(key));
    return status;
}

int decrypt_string(const char* base64_ciphertext, const char* password, char** plaintext) {
    int status = -1;
    unsigned char* encrypted_data = NULL;
    int encrypted_data_len = 0;
    unsigned char key[KEY_LENGTH_BYTES];
    EVP_CIPHER_CTX *ctx = NULL;
    unsigned char* p_plaintext = NULL;
    int len = 0;
    int plaintext_len = 0;

    encrypted_data = base64_decode(base64_ciphertext, &encrypted_data_len);
    if (!encrypted_data) goto cleanup;
    
    size_t min_len = strlen(MAGIC_BYTES) + 1 + SALT_LENGTH_BYTES + IV_LENGTH_BYTES + TAG_LENGTH_BYTES;
    if (encrypted_data_len < min_len) goto cleanup;

    unsigned char* p = encrypted_data;
    if (memcmp(p, MAGIC_BYTES, strlen(MAGIC_BYTES)) != 0) goto cleanup;
    p += strlen(MAGIC_BYTES);
    if (*p++ != VERSION) goto cleanup;

    unsigned char* salt = p; p += SALT_LENGTH_BYTES;
    unsigned char* iv = p; p += IV_LENGTH_BYTES;
    unsigned char* ciphertext = p;
    int ciphertext_len = encrypted_data_len - (p - encrypted_data) - TAG_LENGTH_BYTES;
    if (ciphertext_len < 0) goto cleanup;
    unsigned char* tag = p + ciphertext_len;

    if (PKCS5_PBKDF2_HMAC(password, strlen(password), salt, SALT_LENGTH_BYTES, PBKDF2_ITERATIONS, EVP_sha256(), sizeof(key), key) != 1) goto cleanup;
    
    if (!(ctx = EVP_CIPHER_CTX_new())) goto cleanup;
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL)) goto cleanup;
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, IV_LENGTH_BYTES, NULL)) goto cleanup;
    if (1 != EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv)) goto cleanup;

    p_plaintext = malloc(ciphertext_len + 1);
    if (!p_plaintext) goto cleanup;

    if (1 != EVP_DecryptUpdate(ctx, p_plaintext, &len, ciphertext, ciphertext_len)) goto cleanup;
    plaintext_len = len;

    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, TAG_LENGTH_BYTES, tag)) goto cleanup;

    if (1 != EVP_DecryptFinal_ex(ctx, p_plaintext + len, &len)) goto cleanup;
    plaintext_len += len;
    
    p_plaintext[plaintext_len] = '\0';
    *plaintext = (char*)p_plaintext;
    p_plaintext = NULL; // transfer ownership

    status = 0; // Success

cleanup:
    if (ctx) EVP_CIPHER_CTX_free(ctx);
    if (encrypted_data) free(encrypted_data);
    if (p_plaintext) free(p_plaintext);
    OPENSSL_cleanse(key, sizeof(key));
    return status;
}

int main() {
    // In a real app, use a secure way to get the password
    const char* password = "a_very_strong_password_!@#$";
    const char* testCases[] = {
        "Hello, World!",
        "",
        "This is a longer test sentence to see how it performs with more data.",
        "12345!@#$%^&*()_+-=`~",
        "こんにちは世界" // Unicode test
    };
    int num_test_cases = sizeof(testCases) / sizeof(testCases[0]);

    printf("Running 5 test cases...\n");

    for (int i = 0; i < num_test_cases; ++i) {
        const char* original_plaintext = testCases[i];
        char* encrypted = NULL;
        char* decrypted = NULL;
        
        printf("\n--- Test Case %d ---\n", i + 1);
        printf("Original:    %s\n", original_plaintext);
        
        if (encrypt_string(original_plaintext, password, &encrypted) == 0) {
            printf("Encrypted:   %.60s...\n", encrypted);
            if (decrypt_string(encrypted, password, &decrypted) == 0) {
                printf("Decrypted:   %s\n", decrypted);
                if (strcmp(original_plaintext, decrypted) == 0) {
                    printf("Status:      SUCCESS\n");
                } else {
                    printf("Status:      FAILURE\n");
                }
            } else {
                fprintf(stderr, "Decryption failed for test case %d.\n", i + 1);
            }
        } else {
            fprintf(stderr, "Encryption failed for test case %d.\n", i + 1);
        }
        
        if (encrypted) free(encrypted);
        if (decrypted) free(decrypted);
    }

    return 0;
}