#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <openssl/kdf.h>

#define KEY_SIZE_BYTES 32
#define SALT_SIZE_BYTES 16
#define IV_SIZE_BYTES 12
#define TAG_SIZE_BYTES 16
#define PBKDF2_ITERATIONS 210000
#define MAGIC_BYTES "ENCF"
#define VERSION 1

int derive_key(const char* password, const unsigned char* salt, unsigned char* key) {
    if (PKCS5_PBKDF2_HMAC(password, strlen(password), salt, SALT_SIZE_BYTES, PBKDF2_ITERATIONS, EVP_sha256(), KEY_SIZE_BYTES, key) != 1) {
        return -1;
    }
    return 0;
}

int encrypt_file(const char* input_path, const char* output_path, const char* password) {
    FILE *in_file = NULL, *out_file = NULL;
    unsigned char *plaintext = NULL, *ciphertext = NULL, *key = NULL;
    unsigned char salt[SALT_SIZE_BYTES];
    unsigned char iv[IV_SIZE_BYTES];
    unsigned char tag[TAG_SIZE_BYTES];
    EVP_CIPHER_CTX *ctx = NULL;
    long file_size = 0;
    int len = 0, ciphertext_len = 0;
    int ret = -1;

    char temp_output_path[256];
    snprintf(temp_output_path, sizeof(temp_output_path), "%s.tmp", output_path);

    in_file = fopen(input_path, "rb");
    if (!in_file) goto cleanup;
    
    fseek(in_file, 0, SEEK_END);
    file_size = ftell(in_file);
    fseek(in_file, 0, SEEK_SET);
    
    plaintext = malloc(file_size);
    if (!plaintext) goto cleanup;
    if (fread(plaintext, 1, file_size, in_file) != (size_t)file_size) goto cleanup;

    if (RAND_bytes(salt, sizeof(salt)) != 1) goto cleanup;
    if (RAND_bytes(iv, sizeof(iv)) != 1) goto cleanup;

    key = malloc(KEY_SIZE_BYTES);
    if(!key) goto cleanup;
    if (derive_key(password, salt, key) != 0) goto cleanup;

    ciphertext = malloc(file_size + EVP_MAX_BLOCK_LENGTH);
    if (!ciphertext) goto cleanup;
    
    if (!(ctx = EVP_CIPHER_CTX_new())) goto cleanup;
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1) goto cleanup;
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, sizeof(iv), NULL) != 1) goto cleanup;
    if (EVP_EncryptInit_ex(ctx, NULL, NULL, key, iv) != 1) goto cleanup;
    if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, file_size) != 1) goto cleanup;
    ciphertext_len = len;
    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) goto cleanup;
    ciphertext_len += len;
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, sizeof(tag), tag) != 1) goto cleanup;

    out_file = fopen(temp_output_path, "wb");
    if (!out_file) goto cleanup;
    
    fwrite(MAGIC_BYTES, 1, strlen(MAGIC_BYTES), out_file);
    fputc(VERSION, out_file);
    fwrite(salt, 1, sizeof(salt), out_file);
    fwrite(iv, 1, sizeof(iv), out_file);
    fwrite(ciphertext, 1, ciphertext_len, out_file);
    fwrite(tag, 1, sizeof(tag), out_file);

    if (rename(temp_output_path, output_path) != 0) goto cleanup;

    ret = 0; // Success

cleanup:
    if (in_file) fclose(in_file);
    if (out_file) fclose(out_file);
    if (ret != 0) remove(temp_output_path); // remove temp file on failure
    if (key) { OPENSSL_cleanse(key, KEY_SIZE_BYTES); free(key); }
    if (plaintext) { OPENSSL_cleanse(plaintext, file_size); free(plaintext); }
    if (ciphertext) free(ciphertext);
    if (ctx) EVP_CIPHER_CTX_free(ctx);
    return ret;
}

int decrypt_file(const char* input_path, const char* output_path, const char* password) {
    FILE *in_file = NULL, *out_file = NULL;
    unsigned char *ciphertext = NULL, *plaintext = NULL, *key = NULL;
    unsigned char salt[SALT_SIZE_BYTES], iv[IV_SIZE_BYTES], tag[TAG_SIZE_BYTES];
    char magic_buf[5] = {0};
    int version;
    long file_size = 0, ciphertext_size = 0;
    EVP_CIPHER_CTX *ctx = NULL;
    int len = 0, plaintext_len = 0;
    int ret = -1;

    char temp_output_path[256];
    snprintf(temp_output_path, sizeof(temp_output_path), "%s.tmp", output_path);

    in_file = fopen(input_path, "rb");
    if (!in_file) goto cleanup;

    fread(magic_buf, 1, 4, in_file);
    if (strcmp(magic_buf, MAGIC_BYTES) != 0) goto cleanup;
    version = fgetc(in_file);
    if (version != VERSION) goto cleanup;
    
    if (fread(salt, 1, sizeof(salt), in_file) != sizeof(salt)) goto cleanup;
    if (fread(iv, 1, sizeof(iv), in_file) != sizeof(iv)) goto cleanup;

    fseek(in_file, 0, SEEK_END);
    file_size = ftell(in_file);
    ciphertext_size = file_size - (strlen(MAGIC_BYTES) + 1 + sizeof(salt) + sizeof(iv) + sizeof(tag));
    if (ciphertext_size < 0) goto cleanup;

    ciphertext = malloc(ciphertext_size);
    if (!ciphertext) goto cleanup;
    fseek(in_file, strlen(MAGIC_BYTES) + 1 + sizeof(salt) + sizeof(iv), SEEK_SET);
    if (fread(ciphertext, 1, ciphertext_size, in_file) != (size_t)ciphertext_size) goto cleanup;
    if (fread(tag, 1, sizeof(tag), in_file) != sizeof(tag)) goto cleanup;

    key = malloc(KEY_SIZE_BYTES);
    if(!key) goto cleanup;
    if (derive_key(password, salt, key) != 0) goto cleanup;

    plaintext = malloc(ciphertext_size);
    if (!plaintext) goto cleanup;
    
    if (!(ctx = EVP_CIPHER_CTX_new())) goto cleanup;
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL) != 1) goto cleanup;
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, sizeof(iv), NULL) != 1) goto cleanup;
    if (EVP_DecryptInit_ex(ctx, NULL, NULL, key, iv) != 1) goto cleanup;
    if (EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_size) != 1) goto cleanup;
    plaintext_len = len;
    if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, sizeof(tag), tag) != 1) goto cleanup;

    if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) <= 0) goto cleanup;
    plaintext_len += len;
    
    out_file = fopen(temp_output_path, "wb");
    if (!out_file) goto cleanup;
    fwrite(plaintext, 1, plaintext_len, out_file);

    if (rename(temp_output_path, output_path) != 0) goto cleanup;
    
    ret = 0;

cleanup:
    if (in_file) fclose(in_file);
    if (out_file) fclose(out_file);
    if (ret != 0) remove(temp_output_path);
    if (key) { OPENSSL_cleanse(key, KEY_SIZE_BYTES); free(key); }
    if (ciphertext) free(ciphertext);
    if (plaintext) { OPENSSL_cleanse(plaintext, ciphertext_size); free(plaintext); }
    if (ctx) EVP_CIPHER_CTX_free(ctx);
    return ret;
}

int main(void) {
    printf("Running C tests...\n");
    const char *plaintext_file = "plain.txt";
    const char *encrypted_file = "encrypted.dat";
    const char *decrypted_file = "decrypted.txt";
    const char *password = "securePassword123";
    const char *wrong_password = "wrongPassword123";

    FILE* f = fopen(plaintext_file, "w");
    fputs("This is a test file for encryption.", f);
    fclose(f);
    
    int failed_tests = 0;

    // Test Case 1: Encryption
    if (encrypt_file(plaintext_file, encrypted_file, password) == 0) {
        printf("Test Case 1 (Encryption): PASSED\n");
    } else {
        printf("Test Case 1 (Encryption): FAILED\n");
        failed_tests++;
    }

    // Test Case 2: Decryption
    if (decrypt_file(encrypted_file, decrypted_file, password) == 0) {
        printf("Test Case 2 (Decryption): PASSED\n");
    } else {
        printf("Test Case 2 (Decryption): FAILED\n");
        failed_tests++;
    }

    // Test Case 3: Content verification
    FILE *f1 = fopen(plaintext_file, "rb");
    fseek(f1, 0, SEEK_END); long s1 = ftell(f1); fseek(f1, 0, SEEK_SET); char *b1 = malloc(s1); fread(b1, 1, s1, f1); fclose(f1);
    FILE *f2 = fopen(decrypted_file, "rb");
    fseek(f2, 0, SEEK_END); long s2 = ftell(f2); fseek(f2, 0, SEEK_SET); char *b2 = malloc(s2); fread(b2, 1, s2, f2); fclose(f2);
    if (s1 == s2 && memcmp(b1, b2, s1) == 0) {
        printf("Test Case 3 (Content verification): PASSED\n");
    } else {
        printf("Test Case 3 (Content verification): FAILED\n");
        failed_tests++;
    }
    free(b1); free(b2);

    // Test Case 4: Wrong password
    if (decrypt_file(encrypted_file, decrypted_file, wrong_password) != 0) {
        printf("Test Case 4 (Wrong password): PASSED\n");
    } else {
        printf("Test Case 4 (Wrong password): FAILED\n");
        failed_tests++;
    }

    // Test Case 5: Tampered file
    FILE *f_tamper = fopen(encrypted_file, "r+b");
    if(f_tamper){
        fseek(f_tamper, 50, SEEK_SET);
        fputc(0xFF, f_tamper);
        fclose(f_tamper);
    }
    if (decrypt_file(encrypted_file, decrypted_file, password) != 0) {
        printf("Test Case 5 (Tampered file): PASSED\n");
    } else {
        printf("Test Case 5 (Tampered file): FAILED\n");
        failed_tests++;
    }
    
    remove(plaintext_file);
    remove(encrypted_file);
    remove(decrypted_file);
    
    printf("C tests finished.\n");
    return failed_tests > 0 ? 1 : 0;
}