
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#define TOKEN_BYTES 32
#define MAX_USER_ID_LEN 256
#define HEX_TOKEN_LEN (TOKEN_BYTES * 2 + 1)

/* Convert binary data to hex string
 * Prevents binary data injection and provides safe string representation
 * Returns 0 on success, -1 on failure */
int bytes_to_hex(const unsigned char* bytes, size_t bytes_len, char* hex_out, size_t hex_size) {
    if (!bytes || !hex_out || hex_size < (bytes_len * 2 + 1)) {
        return -1;
    }
    
    for (size_t i = 0; i < bytes_len; i++) {
        /* Use snprintf with bounds checking to prevent buffer overflow (CWE-120) */
        int written = snprintf(hex_out + (i * 2), hex_size - (i * 2), "%02x", bytes[i]);
        if (written != 2) {
            return -1;
        }
    }
    hex_out[bytes_len * 2] = '\0';
    return 0;
}
/* Generate a cryptographically secure authentication token
 * Uses OpenSSL RAND_bytes (CSPRNG) to prevent CWE-338
 * Returns 0 on success, -1 on failure */
int generate_token(char* token_out, size_t token_size) {
    unsigned char token_bytes[TOKEN_BYTES];

    /* Validate output buffer */
    if (!token_out || token_size < HEX_TOKEN_LEN) {
        fprintf(stderr, "Invalid output buffer\n");
        return -1;
    }

    /* Initialize buffer to prevent information leakage */
    memset(token_bytes, 0, TOKEN_BYTES);
    memset(token_out, 0, token_size);

    /* Generate cryptographically secure random bytes
     * RAND_bytes uses OpenSSL's CSPRNG, preventing weak PRNG issues (CWE-338) */
    if (RAND_bytes(token_bytes, TOKEN_BYTES) != 1) {
        fprintf(stderr, "Failed to generate secure random token\n");
        /* Clear sensitive data before returning */
        memset(token_bytes, 0, TOKEN_BYTES);
        return -1;
    }

    /* Convert to hex string for safe storage/transmission */
    int result = bytes_to_hex(token_bytes, TOKEN_BYTES, token_out, token_size);

    /* Clear sensitive data from memory */
    memset(token_bytes, 0, TOKEN_BYTES);

    return result;
}

/* Generate user-bound authentication token
 * Binds token to specific user ID to prevent token reuse
 * Returns 0 on success, -1 on failure */
int generate_user_token(const char* user_id, char* token_out, size_t token_size) {
    unsigned char random_bytes[TOKEN_BYTES];
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;
    EVP_MD_CTX* ctx = NULL;
    int result = -1;

    /* Validate inputs to prevent injection and buffer overflow */
    if (!user_id || !token_out) {
        fprintf(stderr, "Invalid input parameters\n");
        return -1;
    }

    size_t user_id_len = strnlen(user_id, MAX_USER_ID_LEN + 1);
    if (user_id_len == 0 || user_id_len > MAX_USER_ID_LEN) {
        fprintf(stderr, "Invalid userId: must be 1-256 characters\n");
        return -1;
    }

    if (token_size < (SHA256_DIGEST_LENGTH * 2 + 1)) {
        fprintf(stderr, "Output buffer too small\n");
        return -1;
    }

    /* Initialize buffers */
    memset(random_bytes, 0, TOKEN_BYTES);
    memset(hash, 0, EVP_MAX_MD_SIZE);
    memset(token_out, 0, token_size);

    /* Generate secure random bytes */
    if (RAND_bytes(random_bytes, TOKEN_BYTES) != 1) {
        fprintf(stderr, "Failed to generate secure random bytes\n");
        goto cleanup;
    }

    /* Create hash context */
    ctx = EVP_MD_CTX_new();
    if (!ctx) {
        fprintf(stderr, "Failed to create hash context\n");
        goto cleanup;
    }

    /* Initialize SHA-256 hash */
    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1) {
        fprintf(stderr, "Failed to initialize hash\n");
        goto cleanup;
    }

    /* Hash user ID - binds token to specific user */
    if (EVP_DigestUpdate(ctx, user_id, user_id_len) != 1) {
        fprintf(stderr, "Failed to update hash with userId\n");
        goto cleanup;
    }

    /* Hash random bytes - adds unpredictability */
    if (EVP_DigestUpdate(ctx, random_bytes, TOKEN_BYTES) != 1) {
        fprintf(stderr, "Failed to update hash with random data\n");
        goto cleanup;
    }

    /* Finalize hash */
    if (EVP_DigestFinal_ex(ctx, hash, &hash_len) != 1) {
        fprintf(stderr, "Failed to finalize hash\n");
        goto cleanup;
    }

    /* Convert hash to hex string */
    result = bytes_to_hex(hash, hash_len, token_out, token_size);

cleanup:
    /* Securely clear sensitive data from memory */
    memset(random_bytes, 0, TOKEN_BYTES);
    memset(hash, 0, EVP_MAX_MD_SIZE);

    /* Free context if allocated */
    if (ctx) {
        EVP_MD_CTX_free(ctx);
    }

    return result;
}

int main(void) {
    char token[HEX_TOKEN_LEN];
    int status = 0;

    printf("Authentication Token Generator\n");
    printf("================================\n\n");

    /* Test case 1: Generate basic authentication token */
    printf("Test 1 - Basic token generation:\n");
    memset(token, 0, sizeof(token));
    if (generate_token(token, sizeof(token)) == 0) {
        printf("Token: %s\n", token);
        printf("Length: %zu characters\n\n", strlen(token));
    } else {
        fprintf(stderr, "Test 1 failed\n");
        status = 1;
    }

    /* Test case 2: Generate another token (should be different) */
    printf("Test 2 - Second token (should be unique):\n");
    char token2[HEX_TOKEN_LEN];
    memset(token2, 0, sizeof(token2));
    if (generate_token(token2, sizeof(token2)) == 0) {
        printf("Token: %s\n", token2);
        printf("Unique: %s\n\n", (strcmp(token, token2) != 0) ? "Yes" : "No");
    } else {
        fprintf(stderr, "Test 2 failed\n");
        status = 1;
    }

    /* Test case 3: Generate user-bound token */
    printf("Test 3 - User-bound token for 'user123':\n");
    char user_token1[SHA256_DIGEST_LENGTH * 2 + 1];
    memset(user_token1, 0, sizeof(user_token1));
    if (generate_user_token("user123", user_token1, sizeof(user_token1)) == 0) {
        printf("Token: %s\n\n", user_token1);
    } else {
        fprintf(stderr, "Test 3 failed\n");
        status = 1;
    }

    /* Test case 4: Generate another token for same user */
    printf("Test 4 - Another token for 'user123' (should differ):\n");
    char user_token2[SHA256_DIGEST_LENGTH * 2 + 1];
    memset(user_token2, 0, sizeof(user_token2));
    if (generate_user_token("user123", user_token2, sizeof(user_token2)) == 0) {
        printf("Token: %s\n", user_token2);
        printf("Unique: %s\n\n", (strcmp(user_token1, user_token2) != 0) ? "Yes" : "No");
    } else {
        fprintf(stderr, "Test 4 failed\n");
        status = 1;
    }

    /* Test case 5: Generate token for different user */
    printf("Test 5 - Token for 'admin456':\n");
    char user_token3[SHA256_DIGEST_LENGTH * 2 + 1];
    memset(user_token3, 0, sizeof(user_token3));
    if (generate_user_token("admin456", user_token3, sizeof(user_token3)) == 0) {
        printf("Token: %s\n", user_token3);
        printf("Different from user123: %s\n\n", (strcmp(user_token3, user_token1) != 0) ? "Yes" : "No");
    } else {
        fprintf(stderr, "Test 5 failed\n");
        status = 1;
    }

    /* Clear all tokens from memory before exit */
    memset(token, 0, sizeof(token));
    memset(token2, 0, sizeof(token2));
    memset(user_token1, 0, sizeof(user_token1));
    memset(user_token2, 0, sizeof(user_token2));
    memset(user_token3, 0, sizeof(user_token3));

    return status;
}

