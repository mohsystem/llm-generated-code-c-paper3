
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LEN 100
#define MAX_PASSWORD_LEN 100
#define SALT_LEN 16
#define HASH_LEN 32
#define MAX_USERS 10

/* Simulated secure credential store */
/* In production, use environment variables or secure vault */
typedef struct {
    char username[MAX_USERNAME_LEN + 1];
    unsigned char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];
    int active;
} User;

static User user_store[MAX_USERS];
static int user_count = 0;

/* Secure memory cleanup for sensitive data */
void secure_zero(void* ptr, size_t len) {
    if (ptr == NULL || len == 0) return;
    volatile unsigned char* p = (volatile unsigned char*)ptr;
    while (len--) {
        *p++ = 0;
    }
}

/* Generate cryptographically secure random bytes */
int generate_random_bytes(unsigned char* buffer, size_t length) {
    if (buffer == NULL || length == 0) return 0;
    return RAND_bytes(buffer, (int)length) == 1;
}

/* Hash password using PBKDF2-HMAC-SHA-256 with unique salt */
int hash_password(const char* password, const unsigned char* salt, 
                  size_t salt_len, unsigned char* out_hash, size_t hash_len) {
    if (password == NULL || salt == NULL || out_hash == NULL) return 0;
    
    size_t password_len = strlen(password);
    if (password_len == 0 || password_len > MAX_PASSWORD_LEN) return 0;
    
    /* Use PBKDF2 with high iteration count (210000) */
    int result = PKCS5_PBKDF2_HMAC(
        password, (int)password_len,
        salt, (int)salt_len,
        210000,
        EVP_sha256(),
        (int)hash_len,
        out_hash
    );
    
    return result == 1;
}

/* Constant-time comparison to prevent timing attacks */
int constant_time_equals(const unsigned char* a, const unsigned char* b, size_t len) {
    if (a == NULL || b == NULL) return 0;
    
    unsigned char result = 0;
    for (size_t i = 0; i < len; i++) {
        result |= a[i] ^ b[i];
    }
    return result == 0;
}
/* Validate input to prevent injection attacks */
int is_valid_input(const char* input) {
    if (input == NULL) return 0;

    size_t len = strlen(input);
    if (len == 0 || len > 100) return 0;

    /* Allow only safe characters */
    for (size_t i = 0; i < len; i++) {
        char c = input[i];
        if (!isalnum((unsigned char) c) &&
            c != '!' && c != '@' && c != '#' && c != '$' && c != '%' &&
            c != '^' && c != '&' && c != '*' && c != '(' && c != ')' &&
            c != '_' && c != '+' && c != '-' && c != '=' && c != '[' &&
            c != ']' && c != '{' && c != '}' && c != ';' && c != '\'' &&
            c != ':' && c != '"' && c != '\\' && c != '|' && c != ',' &&
            c != '.' && c != '<' && c != '>' && c != '/' && c != '?') {
            return 0;
        }
    }
    return 1;
}

/* Store user with hashed password and unique salt */
int store_user(const char* username, const char* password) {
    if (username == NULL || password == NULL) return 0;
    if (user_count >= MAX_USERS) return 0;

    size_t username_len = strlen(username);
    if (username_len == 0 || username_len > MAX_USERNAME_LEN) return 0;

    unsigned char salt[SALT_LEN];
    unsigned char hash[HASH_LEN];

    /* Generate unique cryptographically secure salt */
    if (!generate_random_bytes(salt, SALT_LEN)) {
        return 0;
    }

    /* Hash password with salt */
    if (!hash_password(password, salt, SALT_LEN, hash, HASH_LEN)) {
        secure_zero(salt, SALT_LEN);
        secure_zero(hash, HASH_LEN);
        return 0;
    }

    /* Store user credentials */
    strncpy(user_store[user_count].username, username, MAX_USERNAME_LEN);
    user_store[user_count].username[MAX_USERNAME_LEN] = '\0';
    memcpy(user_store[user_count].salt, salt, SALT_LEN);
    memcpy(user_store[user_count].hash, hash, HASH_LEN);
    user_store[user_count].active = 1;
    user_count++;

    /* Clear sensitive data */
    secure_zero(salt, SALT_LEN);
    secure_zero(hash, HASH_LEN);

    return 1;
}

/* Find user by username */
User* find_user(const char* username) {
    if (username == NULL) return NULL;

    for (int i = 0; i < user_count; i++) {
        if (user_store[i].active && strcmp(user_store[i].username, username) == 0) {
            return &user_store[i];
        }
    }
    return NULL;
}

/* Check credentials securely */
int check_credentials(const char* username, const char* password) {
    unsigned char provided_hash[HASH_LEN];
    int result = 0;

    /* Validate inputs before processing */
    if (!is_valid_input(username) || !is_valid_input(password)) {
        return 0;
    }

    /* Find user */
    User* user = find_user(username);

    if (user == NULL) {
        /* Perform dummy computation to prevent timing attacks */
        unsigned char dummy_salt[SALT_LEN];
        unsigned char dummy_hash[HASH_LEN];
        generate_random_bytes(dummy_salt, SALT_LEN);
        hash_password(password, dummy_salt, SALT_LEN, dummy_hash, HASH_LEN);
        secure_zero(dummy_salt, SALT_LEN);
        secure_zero(dummy_hash, HASH_LEN);
        return 0;
    }

    /* Hash provided password with stored salt */
    if (!hash_password(password, user->salt, SALT_LEN, provided_hash, HASH_LEN)) {
        secure_zero(provided_hash, HASH_LEN);
        return 0;
    }

    /* Use constant-time comparison */
    result = constant_time_equals(user->hash, provided_hash, HASH_LEN);

    /* Clear sensitive data */
    secure_zero(provided_hash, HASH_LEN);

    return result;
}

/* Parse query parameter value */
char* get_param_value(const char* query, const char* param_name) {
    if (query == NULL || param_name == NULL) return NULL;

    char search[MAX_USERNAME_LEN + 10];
    int ret = snprintf(search, sizeof(search), "%s=", param_name);
    if (ret < 0 || (size_t) ret >= sizeof(search)) return NULL;

    const char* pos = strstr(query, search);
    if (pos == NULL) return NULL;

    pos += strlen(search);
    const char* end = strchr(pos, '&');
    size_t len = end ? (size_t) (end - pos) : strlen(pos);

    if (len > MAX_PASSWORD_LEN) return NULL;

    char* value = (char*) malloc(len + 1);
    if (value == NULL) return NULL;

    memcpy(value, pos, len);
    value[len] = '\0';

    return value;
}

/* Simulate check_mod function */
const char* check_mod(const char* query) {
    char* username = NULL;
    char* password = NULL;
    const char* result = "false";
    
    if (query == NULL) {
        return "false";
    }
    
    /* Parse query parameters */
    username = get_param_value(query, "username");
    password = get_param_value(query, "password");
    
    /* Check if both parameters are present */
    if (username == NULL || password == NULL) {
        result = "false";
        goto cleanup;
    }
    
    /* Check credentials */
    if (check_credentials(username, password)) {
        result = "true";
    } else {
        result = "false";
    }
    
cleanup:
    /* Clear and free sensitive data */
    if (password != NULL) {
        secure_zero(password, strlen(password));
        free(password);
    }
    if (username != NULL) {
        free(username);
    }
    
    return result;
}

int main(void) {
    /* Initialize OpenSSL */
    OpenSSL_add_all_algorithms();
    
    /* Initialize test users with secure passwords */
    store_user("admin", "SecurePass123!");
    store_user("user1", "MyPassword456!");
    store_user("testuser", "TestPass789!");
    store_user("moderator", "ModPass321!");
    store_user("developer", "DevPass654!");
    
    printf("Test cases:\\n");
    
    /* Test case 1: Valid credentials */
    const char* result1 = check_mod("username=admin&password=SecurePass123!");
    printf("1. Valid admin: %s\\n", result1);
    
    /* Test case 2: Valid credentials */
    const char* result2 = check_mod("username=user1&password=MyPassword456!");
    printf("2. Valid user1: %s\\n", result2);
    
    /* Test case 3: Invalid password */
    const char* result3 = check_mod("username=admin&password=wrong");
    printf("3. Invalid password: %s\\n", result3);
    
    /* Test case 4: Invalid user */
    const char* result4 = check_mod("username=invalid&password=test");
    printf("4. Invalid user: %s\\n", result4);
    
    /* Test case 5: Missing parameters */
    const char* result5 = check_mod("username=admin");
    printf("5. Missing params: %s\\n", result5);
    
    /* Cleanup OpenSSL */
    EVP_cleanup();
    
    return 0;
}
