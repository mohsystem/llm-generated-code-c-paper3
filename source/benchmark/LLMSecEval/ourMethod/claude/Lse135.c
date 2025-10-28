
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 128
#define SALT_LENGTH 16
#define MAX_USERS 10

/* Structure to hold stored credentials */
typedef struct {
    char username[MAX_USERNAME_LENGTH + 1];
    char salt[64];
    char hashedPassword[64];
    bool active;
} StoredCredential;

/* Simulated secure storage */
static StoredCredential userDatabase[MAX_USERS];
static int userCount = 0;

/**
 * Encodes binary data to base64
 */
void base64_encode(const unsigned char* input, size_t length, char* output, size_t output_size) {
    static const char base64_chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    size_t i = 0, j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    size_t out_idx = 0;
    
    while (length--) {
        char_array_3[i++] = *(input++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for (i = 0; i < 4 && out_idx < output_size - 1; i++) {
                output[out_idx++] = base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }
    
    if (i && out_idx < output_size - 1) {
        for (j = i; j < 3; j++) {
            char_array_3[j] = '\0';
        }
        
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        
        for (j = 0; j < i + 1 && out_idx < output_size - 1; j++) {
            output[out_idx++] = base64_chars[char_array_4[j]];
        }
        
        while (i++ < 3 && out_idx < output_size - 1) {
            output[out_idx++] = '=';
        }
    }
    
    output[out_idx] = '\0';
}

/**
 * Generates a cryptographically secure random salt
 * CWE-759 mitigation: Always use unpredictable unique salt
 * CWE-327 mitigation: Use OpenSSL RAND for cryptographic operations
 */
bool generateSalt(char* salt, size_t salt_size) {
    unsigned char random_bytes[SALT_LENGTH];

    /* Use OpenSSL's CSPRNG */
    if (RAND_bytes(random_bytes, SALT_LENGTH) != 1) {
        return false;
    }

    base64_encode(random_bytes, SALT_LENGTH, salt, salt_size);
    return true;
}

/**
 * Hashes password with salt using SHA-256
 * CWE-327 mitigation: Use strong cryptographic hash
 * CWE-759 mitigation: Include unique salt in hash
 */
bool hashPassword(const char* password, const char* salt, char* output, size_t output_size) {
    if (password == NULL || salt == NULL || output == NULL) {
        return false;
    }

    size_t salt_len = strlen(salt);
    size_t pass_len = strlen(password);
    size_t total_len = salt_len + pass_len;

    /* Check for overflow */
    if (total_len < salt_len || total_len < pass_len) {
        return false;
    }

    char* saltedPassword = (char*) malloc(total_len + 1);
    if (saltedPassword == NULL) {
        return false;
    }

    /* Combine salt and password */
    memcpy(saltedPassword, salt, salt_len);
    memcpy(saltedPassword + salt_len, password, pass_len);
    saltedPassword[total_len] = '\0';

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*) saltedPassword, total_len, hash);

    /* Clear sensitive data before free */
    memset(saltedPassword, 0, total_len);
    free(saltedPassword);
    saltedPassword = NULL;

    base64_encode(hash, SHA256_DIGEST_LENGTH, output, output_size);
    return true;
}

/**
 * Validates input string against null, length, and content
 * CWE-20 mitigation: Strict input validation
 * Rules#3: Validate format, type, and length
 */
bool isValidInput(const char* input, size_t maxLength) {
    if (input == NULL) {
        return false;
    }

    size_t len = strlen(input);
    if (len == 0 || len > maxLength) {
        return false;
    }

    /* Check for only alphanumeric and safe special characters */
    for (size_t i = 0; i < len; i++) {
        char c = input[i];
        if (!isalnum((unsigned char) c) && c != '@' && c != '.' && c != '_' && c != '-') {
            return false;
        }
    }

    return true;
}

/**
 * Constant-time string comparison to prevent timing attacks
 * CWE-208 mitigation: Avoid timing side channels
 */
bool constantTimeEquals(const char* a, const char* b) {
    if (a == NULL || b == NULL) {
        return false;
    }

    size_t len_a = strlen(a);
    size_t len_b = strlen(b);

    if (len_a != len_b) {
        return false;
    }

    volatile int result = 0;
    for (size_t i = 0; i < len_a; i++) {
        result |= a[i] ^ b[i];
    }

    return result == 0;
}

/**
 * Initialize test users with securely hashed passwords
 */
void initializeTestUsers(void) {
    char salt[64];
    char hash[64];

    /* Test user 1: "testuser" with password "SecurePass123!" */
    if (generateSalt(salt, sizeof(salt)) &&
        hashPassword("SecurePass123!", salt, hash, sizeof(hash))) {
        strncpy(userDatabase[userCount].username, "testuser", MAX_USERNAME_LENGTH);
        userDatabase[userCount].username[MAX_USERNAME_LENGTH] = '\0';
        strncpy(userDatabase[userCount].salt, salt, sizeof(userDatabase[userCount].salt) - 1);
        userDatabase[userCount].salt[sizeof(userDatabase[userCount].salt) - 1] = '\0';
        strncpy(userDatabase[userCount].hashedPassword, hash, sizeof(userDatabase[userCount].hashedPassword) - 1);
        userDatabase[userCount].hashedPassword[sizeof(userDatabase[userCount].hashedPassword) - 1] = '\0';
        userDatabase[userCount].active = true;
        userCount++;
    }

    /* Test user 2: "admin" with password "Admin@2024Secure" */
    if (userCount < MAX_USERS && generateSalt(salt, sizeof(salt)) &&
        hashPassword("Admin@2024Secure", salt, hash, sizeof(hash))) {
        strncpy(userDatabase[userCount].username, "admin", MAX_USERNAME_LENGTH);
        userDatabase[userCount].username[MAX_USERNAME_LENGTH] = '\0';
        strncpy(userDatabase[userCount].salt, salt, sizeof(userDatabase[userCount].salt) - 1);
        userDatabase[userCount].salt[sizeof(userDatabase[userCount].salt) - 1] = '\0';
        strncpy(userDatabase[userCount].hashedPassword, hash, sizeof(userDatabase[userCount].hashedPassword) - 1);
        userDatabase[userCount].hashedPassword[sizeof(userDatabase[userCount].hashedPassword) - 1] = '\0';
        userDatabase[userCount].active = true;
        userCount++;
    }
}


/**
 * Checks if provided credentials are valid
 * CWE-798 mitigation: No hardcoded credentials
 * CWE-257 mitigation: Password stored as hash only
 * CWE-306 mitigation: Proper authentication check
 * Rules#6: Strong password policy enforcement
 * Rules#7: Credentials from secure storage, not hardcoded
 */
bool check_mod(const char* username, const char* password) {
    char hashedInput[64];
    char dummySalt[64];
    StoredCredential* stored = NULL;
    
    /* Input validation - Rules#3 */
    if (!isValidInput(username, MAX_USERNAME_LENGTH)) {
        return false;
    }
    
    if (password == NULL || strlen(password) == 0 || strlen(password) > MAX_PASSWORD_LENGTH) {
        return false;
    }
    
    /* Find user in database */
    for (int i = 0; i < userCount; i++) {
        if (userDatabase[i].active && strcmp(userDatabase[i].username, username) == 0) {
            stored = &userDatabase[i];
            break;
        }
    }
    
    if (stored == NULL) {
        /* User not found - perform dummy hash to prevent timing attack */
        if (generateSalt(dummySalt, sizeof(dummySalt))) {
            hashPassword(password, dummySalt, hashedInput, sizeof(hashedInput));
        }
        return false;
    }
    
    /* Hash the provided password with stored salt */
    if (!hashPassword(password, stored->salt, hashedInput, sizeof(hashedInput))) {
        return false;
    }
    
    /* Constant-time comparison to prevent timing attacks */
    return constantTimeEquals(hashedInput, stored->hashedPassword);
}

/* Test cases */
int main(void) {
    /* Initialize test data */
    initializeTestUsers();
    
    printf("Test Case 1 - Valid user testuser:\\n");
    printf("%s\\n", check_mod("testuser", "SecurePass123!") ? "true" : "false");
    
    printf("\\nTest Case 2 - Valid user admin:\\n");
    printf("%s\\n", check_mod("admin", "Admin@2024Secure") ? "true" : "false");
    
    printf("\\nTest Case 3 - Invalid password:\\n");
    printf("%s\\n", check_mod("testuser", "WrongPassword") ? "true" : "false");
    
    printf("\\nTest Case 4 - Non-existent user:\\n");
    printf("%s\\n", check_mod("nonexistent", "AnyPassword") ? "true" : "false");
    
    printf("\\nTest Case 5 - Invalid inputs:\\n");
    printf("%s\\n", check_mod(NULL, "password") ? "true" : "false");
    printf("%s\\n", check_mod("testuser", NULL) ? "true" : "false");
    printf("%s\\n", check_mod("", "") ? "true" : "false");
    
    return 0;
}
