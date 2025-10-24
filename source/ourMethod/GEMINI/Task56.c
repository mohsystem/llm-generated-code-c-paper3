#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>

#include <openssl/evp.h>
#include <openssl/rand.h>

// Note: This code requires OpenSSL. Compile with: gcc task.c -o task -lssl -lcrypto

// --- Start of Base64 implementation ---
static const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* base64_encode(const unsigned char *data, size_t input_length) {
    size_t output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(output_length + 1);
    if (encoded_data == NULL) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;
        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
        encoded_data[j++] = b64_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = b64_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = b64_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = b64_table[(triple >> 0 * 6) & 0x3F];
    }

    static const int mod_table[] = {0, 2, 1};
    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[output_length - 1 - i] = '=';

    encoded_data[output_length] = '\0';
    return encoded_data;
}

unsigned char* base64_decode(const char *data, size_t *output_length) {
    size_t input_length = strlen(data);
    if (input_length % 4 != 0) return NULL;

    *output_length = input_length / 4 * 3;
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;
    
    unsigned char *decoded_data = malloc(*output_length);
    if (decoded_data == NULL) return NULL;
    
    char *b64_inv = calloc(256, sizeof(char));
    if(!b64_inv) { free(decoded_data); return NULL; }
    for(size_t i = 0; i < 64; i++) b64_inv[(unsigned char)b64_table[i]] = i;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : b64_inv[(unsigned char)data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : b64_inv[(unsigned char)data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : b64_inv[(unsigned char)data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : b64_inv[(unsigned char)data[i++]];
        uint32_t triple = (sextet_a << 3 * 6) + (sextet_b << 2 * 6) + (sextet_c << 1 * 6) + (sextet_d << 0 * 6);
        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }
    free(b64_inv);
    return decoded_data;
}
// --- End of Base64 implementation ---

#define AES_KEY_SIZE_BYTES (256 / 8)
#define GCM_IV_LENGTH_BYTES 12
#define GCM_TAG_LENGTH_BYTES 16

char* generate_token(const char* user_id, const unsigned char* key, int validity_seconds) {
    if (!user_id || !key) return NULL;

    char payload[256];
    long long expiration_time = time(NULL) + validity_seconds;
    int payload_len = snprintf(payload, sizeof(payload), "%s:%lld", user_id, expiration_time);
    if (payload_len < 0 || (size_t)payload_len >= sizeof(payload)) return NULL;

    unsigned char iv[GCM_IV_LENGTH_BYTES];
    if (RAND_bytes(iv, sizeof(iv)) != 1) return NULL;

    EVP_CIPHER_CTX *ctx = NULL;
    unsigned char* ciphertext = NULL;
    unsigned char tag[GCM_TAG_LENGTH_BYTES];
    unsigned char* token_bytes = NULL;
    char* b64_token = NULL;
    int len = 0;
    int ciphertext_len = 0;

    if (!(ctx = EVP_CIPHER_CTX_new())) goto cleanup;
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, key, iv)) goto cleanup;
    
    ciphertext = malloc(payload_len + EVP_CIPHER_block_size(EVP_aes_256_gcm()));
    if (!ciphertext) goto cleanup;

    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, (const unsigned char*)payload, payload_len)) goto cleanup;
    ciphertext_len = len;

    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) goto cleanup;
    ciphertext_len += len;
    
    if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, GCM_TAG_LENGTH_BYTES, tag)) goto cleanup;

    size_t token_bytes_len = GCM_IV_LENGTH_BYTES + ciphertext_len + GCM_TAG_LENGTH_BYTES;
    token_bytes = malloc(token_bytes_len);
    if (!token_bytes) goto cleanup;

    memcpy(token_bytes, iv, GCM_IV_LENGTH_BYTES);
    memcpy(token_bytes + GCM_IV_LENGTH_BYTES, ciphertext, ciphertext_len);
    memcpy(token_bytes + GCM_IV_LENGTH_BYTES + ciphertext_len, tag, GCM_TAG_LENGTH_BYTES);
    
    b64_token = base64_encode(token_bytes, token_bytes_len);

cleanup:
    if (ctx) EVP_CIPHER_CTX_free(ctx);
    free(ciphertext);
    free(token_bytes);
    return b64_token;
}

char* validate_token(const char* token, const unsigned char* key) {
    if (!token || !key) return NULL;

    size_t token_bytes_len;
    unsigned char* token_bytes = base64_decode(token, &token_bytes_len);
    if (!token_bytes) return NULL;

    if (token_bytes_len < GCM_IV_LENGTH_BYTES + GCM_TAG_LENGTH_BYTES) {
        free(token_bytes);
        return NULL;
    }

    size_t ciphertext_len = token_bytes_len - GCM_IV_LENGTH_BYTES - GCM_TAG_LENGTH_BYTES;
    unsigned char* ciphertext = malloc(ciphertext_len);
    if (!ciphertext) {
        free(token_bytes);
        return NULL;
    }

    memcpy(ciphertext, token_bytes + GCM_IV_LENGTH_BYTES, ciphertext_len);
    
    EVP_CIPHER_CTX *ctx = NULL;
    unsigned char* plaintext = NULL;
    char* user_id_out = NULL;

    if (!(ctx = EVP_CIPHER_CTX_new())) goto v_cleanup;
    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, key, token_bytes)) goto v_cleanup;

    plaintext = malloc(ciphertext_len);
    if (!plaintext) goto v_cleanup;

    int len;
    if (!EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) goto v_cleanup;
    int plaintext_len = len;

    if (!EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, GCM_TAG_LENGTH_BYTES, token_bytes + GCM_IV_LENGTH_BYTES + ciphertext_len)) goto v_cleanup;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) goto v_cleanup; // Tag mismatch
    plaintext_len += len;
    
    char payload[256];
    size_t copy_len = plaintext_len < sizeof(payload) - 1 ? plaintext_len : sizeof(payload) - 1;
    memcpy(payload, plaintext, copy_len);
    payload[copy_len] = '\0';

    char* separator = strchr(payload, ':');
    if (!separator) goto v_cleanup;
    
    *separator = '\0';
    if (atoll(separator + 1) < time(NULL)) {
        printf("Token expired.\n");
        goto v_cleanup;
    }

    user_id_out = malloc(strlen(payload) + 1);
    if (user_id_out) strcpy(user_id_out, payload);
    
v_cleanup:
    if (ctx) EVP_CIPHER_CTX_free(ctx);
    free(ciphertext);
    free(plaintext);
    free(token_bytes);
    return user_id_out;
}

int main() {
    unsigned char secret_key[AES_KEY_SIZE_BYTES];
    unsigned char wrong_key[AES_KEY_SIZE_BYTES];
    if (RAND_bytes(secret_key, sizeof(secret_key)) != 1) return 1;
    if (RAND_bytes(wrong_key, sizeof(wrong_key)) != 1) return 1;
    
    const char* user_id = "user-12345";
    int validity_seconds = 3600;

    printf("--- Test Case 1: Generate and validate a valid token ---\n");
    char* token = generate_token(user_id, secret_key, validity_seconds);
    if (token) {
        printf("Generated Token: %s\n", token);
        char* validated_user_id = validate_token(token, secret_key);
        if (validated_user_id && strcmp(validated_user_id, user_id) == 0) {
            printf("Validation result: SUCCESS\n");
            printf("Validated User ID: %s\n", validated_user_id);
        } else {
            printf("Validation result: FAILURE\n");
        }
        free(validated_user_id);
    } else {
        printf("Token generation failed.\n");
    }
    
    printf("\n--- Test Case 2: Validate an expired token ---\n");
    char* expired_token = generate_token(user_id, secret_key, -1);
    if (expired_token) {
        char* validated_user_id = validate_token(expired_token, secret_key);
        printf("Validation result: %s\n", !validated_user_id ? "SUCCESS (expired as expected)" : "FAILURE");
        free(validated_user_id);
        free(expired_token);
    }

    printf("\n--- Test Case 3: Validate a tampered token ---\n");
    if (token) {
        token[strlen(token) - 2] = 'Z';
        printf("Tampered Token: %s\n", token);
        char* validated_user_id = validate_token(token, secret_key);
        printf("Validation result: %s\n", !validated_user_id ? "SUCCESS (tampering detected)" : "FAILURE");
        free(validated_user_id);
    }

    printf("\n--- Test Case 4: Validate with a wrong key ---\n");
    if (token) {
        token[strlen(token) - 2] = 'A'; // Revert tampering for this test
        char* validated_user_id = validate_token(token, wrong_key);
        printf("Validation result: %s\n", !validated_user_id ? "SUCCESS (wrong key detected)" : "FAILURE");
        free(validated_user_id);
    }

    printf("\n--- Test Case 5: Validate a malformed token ---\n");
    const char* malformed_token = "this-is-not-a-valid-token";
    char* validated_user_id = validate_token(malformed_token, secret_key);
    printf("Validation result: %s\n", !validated_user_id ? "SUCCESS (malformed token detected)" : "FAILURE");
    free(validated_user_id);

    free(token);
    return 0;
}