
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

/* Password reset functionality with secure token generation and validation */
/* Uses PBKDF2-HMAC-SHA256 for password hashing with unique salts */

#define SALT_SIZE 16
#define HASH_SIZE 32
#define TOKEN_SIZE 32
#define PBKDF2_ITERATIONS 210000
#define TOKEN_EXPIRY_SECONDS 3600
#define MAX_USERNAME_LEN 256
#define MAX_PASSWORD_LEN 256

typedef struct {
    char username[MAX_USERNAME_LEN];
    unsigned char password_hash[HASH_SIZE];
    unsigned char salt[SALT_SIZE];
    unsigned char reset_token[TOKEN_SIZE];
    int has_token;
    long token_expiry;
} UserRecord;

/* Secure comparison to prevent timing attacks */
static int constant_time_compare(const unsigned char* a, const unsigned char* b, size_t len) {
    unsigned char result = 0;
    size_t i;
    
    if (!a || !b) {
        return 0;
    }
    
    for (i = 0; i < len; i++) {
        result |= a[i] ^ b[i];
    }
    return result == 0;
}

/* Generate cryptographically secure random bytes */
static int generate_random_bytes(unsigned char* buffer, int size) {
    if (!buffer || size <= 0) {
        return 0;
    }
    /* Use OpenSSL's CSPRNG */
    if (RAND_bytes(buffer, size) != 1) {
        return 0;
    }
    return 1;
}

/* Hash password with PBKDF2-HMAC-SHA256 */
static int hash_password(const char* password, const unsigned char* salt, unsigned char* hash) {
    size_t password_len;

    if (!password || !salt || !hash) {
        return 0;
    }

    password_len = strnlen(password, MAX_PASSWORD_LEN);
    if (password_len == 0 || password_len >= MAX_PASSWORD_LEN) {
        return 0;
    }

    /* Use PBKDF2 with SHA-256 and 210,000 iterations */
    if (PKCS5_PBKDF2_HMAC(password, (int)password_len,
                          salt, SALT_SIZE,
                          PBKDF2_ITERATIONS,
                          EVP_sha256(),
                          HASH_SIZE, hash) != 1) {
        return 0;
    }
    return 1;
}

/* Validate password strength */
static int validate_password_strength(const char* password) {
    size_t len;
    size_t i;
    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;

    if (!password) {
        return 0;
    }

    len = strnlen(password, MAX_PASSWORD_LEN);
    if (len < 8 || len >= MAX_PASSWORD_LEN) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (isupper((unsigned char)password[i])) {
            has_upper = 1;
        } else if (islower((unsigned char)password[i])) {
            has_lower = 1;
        } else if (isdigit((unsigned char)password[i])) {
            has_digit = 1;
        } else {
            has_special = 1;
        }
    }

    return has_upper && has_lower && has_digit && has_special;
}

/* Initialize user record */
void init_user_record(UserRecord* user) {
    if (!user) {
        return;
    }
    memset(user, 0, sizeof(UserRecord));
}

/* Generate a secure password reset token */
int generate_reset_token(UserRecord* user) {
    if (!user || strnlen(user->username, MAX_USERNAME_LEN) == 0) {
        return 0;
    }

    /* Generate cryptographically secure random token */
    if (!generate_random_bytes(user->reset_token, TOKEN_SIZE)) {
        memset(user->reset_token, 0, TOKEN_SIZE);
        user->has_token = 0;
        return 0;
    }

    /* Set token expiry (current time + 1 hour) */
    user->token_expiry = (long)time(NULL) + TOKEN_EXPIRY_SECONDS;
    user->has_token = 1;
    return 1;
}

/* Validate reset token */
int validate_reset_token(const UserRecord* user, const unsigned char* token) {
    long current_time;

    if (!user || !token || !user->has_token) {
        return 0;
    }

    /* Check token expiry */
    current_time = (long)time(NULL);
    if (current_time > user->token_expiry) {
        return 0;
    }

    /* Constant-time comparison to prevent timing attacks */
    return constant_time_compare(user->reset_token, token, TOKEN_SIZE);
}

/* Hash and store new password */
int reset_password(UserRecord* user, const char* new_password) {
    if (!user || !new_password) {
        return 0;
    }

    /* Validate password strength */
    if (!validate_password_strength(new_password)) {
        return 0;
    }

    /* Generate new unique salt */
    if (!generate_random_bytes(user->salt, SALT_SIZE)) {
        memset(user->salt, 0, SALT_SIZE);
        return 0;
    }

    /* Hash password with new salt */
    if (!hash_password(new_password, user->salt, user->password_hash)) {
        /* Clear sensitive data on failure */
        memset(user->password_hash, 0, HASH_SIZE);
        memset(user->salt, 0, SALT_SIZE);
        return 0;
    }

    /* Clear reset token after successful password reset */
    memset(user->reset_token, 0, TOKEN_SIZE);
    user->has_token = 0;
    user->token_expiry = 0;

    return 1;
}

/* Verify password against stored hash */
int verify_password(const UserRecord* user, const char* password) {
    unsigned char computed_hash[HASH_SIZE];

    if (!user || !password) {
        return 0;
    }

    memset(computed_hash, 0, HASH_SIZE);

    if (!hash_password(password, user->salt, computed_hash)) {
        memset(computed_hash, 0, HASH_SIZE);
        return 0;
    }

    int result = constant_time_compare(user->password_hash, computed_hash, HASH_SIZE);

    /* Clear computed hash from memory */
    memset(computed_hash, 0, HASH_SIZE);

    return result;
}

int main(void) {
    UserRecord user;
    unsigned char saved_token[TOKEN_SIZE];
    unsigned char invalid_token[TOKEN_SIZE];

    printf("=== Password Reset Functionality Test Cases ===\n");

    /* Test Case 1: Create user and set initial password */
    printf("\nTest 1: Create user with initial password\n");
    init_user_record(&user);
    strncpy(user.username, "testuser1", MAX_USERNAME_LEN - 1);
    user.username[MAX_USERNAME_LEN - 1] = '\0';

    if (reset_password(&user, "SecureP@ss123")) {
        printf("Initial password set successfully\n");
    } else {
        printf("Failed to set initial password\n");
    }

    /* Test Case 2: Generate reset token */
    printf("\nTest 2: Generate password reset token\n");
    if (generate_reset_token(&user)) {
        printf("Reset token generated (length: %d bytes)\n", TOKEN_SIZE);
        memcpy(saved_token, user.reset_token, TOKEN_SIZE);
    } else {
        printf("Failed to generate reset token\n");
    }

    /* Test Case 3: Validate correct reset token */
    printf("\nTest 3: Validate correct reset token\n");
    if (validate_reset_token(&user, saved_token)) {
        printf("Token validation successful\n");
    } else {
        printf("Token validation failed\n");
    }

    /* Test Case 4: Validate incorrect reset token */
    printf("\nTest 4: Validate incorrect reset token\n");
    memset(invalid_token, 0xFF, TOKEN_SIZE);
    if (!validate_reset_token(&user, invalid_token)) {
        printf("Invalid token correctly rejected\n");
    } else {
        printf("Invalid token incorrectly accepted\n");
    }

    /* Test Case 5: Reset password with valid token and verify */
    printf("\nTest 5: Reset password and verify\n");
    if (reset_password(&user, "NewSecure@Pass456")) {
        printf("Password reset successfully\n");
        if (verify_password(&user, "NewSecure@Pass456")) {
            printf("New password verified successfully\n");
        } else {
            printf("New password verification failed\n");
        }
        if (!verify_password(&user, "SecureP@ss123")) {
            printf("Old password correctly rejected\n");
        } else {
            printf("Old password incorrectly accepted\n");
        }
    } else {
        printf("Failed to reset password\n");
    }

    /* Clear sensitive data before exit */
    memset(&user, 0, sizeof(UserRecord));
    memset(saved_token, 0, TOKEN_SIZE);
    memset(invalid_token, 0, TOKEN_SIZE);

    return 0;
}

