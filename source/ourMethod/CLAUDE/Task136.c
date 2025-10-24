
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

/* Constants for security parameters */
#define SALT_SIZE 16
#define HASH_SIZE 32
#define PBKDF2_ITERATIONS 210000
#define MAX_USERS 100
#define MAX_USERNAME_LEN 64
#define MAX_PASSWORD_LEN 128

/* Structure to hold user credentials */
typedef struct {
    char username[MAX_USERNAME_LEN + 1];
    uint8_t salt[SALT_SIZE];
    uint8_t password_hash[HASH_SIZE];
    int active;
} UserCredentials;

/* User database */
typedef struct {
    UserCredentials users[MAX_USERS];
    int user_count;
} UserDatabase;

/* Securely clear memory containing sensitive data - CWE-14 mitigation */
void secure_clear(void* ptr, size_t len) {
    if (ptr == NULL || len == 0) return;
    volatile unsigned char* p = (volatile unsigned char*)ptr;
    while (len--) *p++ = 0;
}
/* Generate cryptographically secure random salt - CWE-338 mitigation */
int generate_salt(uint8_t* salt) {
    if (salt == NULL) {
        return 0;
    }

    /* Use OpenSSL's secure random generator */
    if (RAND_bytes(salt, SALT_SIZE) != 1) {
        return 0;
    }
    return 1;
}

/* Hash password with PBKDF2-HMAC-SHA256 - CWE-327, CWE-759 mitigation */
int hash_password(const char* password, const uint8_t* salt, uint8_t* hash) {
    size_t password_len;

    /* Input validation - CWE-20 mitigation */
    if (password == NULL || salt == NULL || hash == NULL) {
        return 0;
    }

    password_len = strlen(password);
    if (password_len == 0 || password_len > MAX_PASSWORD_LEN) {
        return 0;
    }

    /* Use PBKDF2 with SHA-256, unique salt, and sufficient iterations */
    if (PKCS5_PBKDF2_HMAC(password, (int)password_len,
                          salt, SALT_SIZE,
                          PBKDF2_ITERATIONS, EVP_sha256(),
                          HASH_SIZE, hash) != 1) {
        return 0;
    }

    return 1;
}

/* Constant-time comparison to prevent timing attacks - CWE-208 mitigation */
int constant_time_compare(const uint8_t* a, const uint8_t* b, size_t len) {
    size_t i;
    int result = 0;

    if (a == NULL || b == NULL) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        result |= a[i] ^ b[i];
    }
    return result == 0;
}

/* Validate username format - CWE-20 mitigation */
int validate_username(const char* username) {
    size_t len;
    size_t i;

    if (username == NULL) {
        return 0;
    }

    len = strlen(username);
    if (len == 0 || len > MAX_USERNAME_LEN) {
        return 0;
    }

    /* Check for alphanumeric characters, underscore, and hyphen only */
    for (i = 0; i < len; i++) {
        if (!isalnum((unsigned char)username[i]) &&
            username[i] != '_' && username[i] != '-') {
            return 0;
        }
    }

    return 1;
}

/* Initialize user database */
void init_database(UserDatabase* db) {
    if (db == NULL) return;
    memset(db, 0, sizeof(UserDatabase));
    db->user_count = 0;
}

/* Register a new user */
int register_user(UserDatabase* db, const char* username, const char* password) {
    UserCredentials* new_user;
    int i;
    size_t password_len;

    /* Input validation - CWE-20 mitigation */
    if (db == NULL || username == NULL || password == NULL) {
        return 0;
    }

    if (!validate_username(username)) {
        return 0;
    }

    password_len = strlen(password);
    if (password_len == 0 || password_len > MAX_PASSWORD_LEN) {
        return 0;
    }

    /* Check if database is full - CWE-119 mitigation */
    if (db->user_count >= MAX_USERS) {
        return 0;
    }

    /* Check if user already exists */
    for (i = 0; i < db->user_count; i++) {
        if (db->users[i].active && strcmp(db->users[i].username, username) == 0) {
            return 0; /* User already exists */
        }
    }

    /* Get pointer to new user slot */
    new_user = &db->users[db->user_count];

    /* Copy username with bounds check - CWE-120 mitigation */
    strncpy(new_user->username, username, MAX_USERNAME_LEN);
    new_user->username[MAX_USERNAME_LEN] = '\0';

    /* Generate unique salt - CWE-759 mitigation */
    if (!generate_salt(new_user->salt)) {
        memset(new_user, 0, sizeof(UserCredentials));
        return 0;
    }

    /* Hash password with salt */
    if (!hash_password(password, new_user->salt, new_user->password_hash)) {
        secure_clear(new_user, sizeof(UserCredentials));
        return 0;
    }

    new_user->active = 1;
    db->user_count++;

    return 1;
}

/* Authenticate a user */
int authenticate_user(UserDatabase* db, const char* username, const char* password) {
    int i;
    UserCredentials* user_creds = NULL;
    uint8_t computed_hash[HASH_SIZE];
    int result;
    size_t password_len;

    /* Input validation - CWE-20 mitigation */
    if (db == NULL || username == NULL || password == NULL) {
        return 0;
    }

    if (!validate_username(username)) {
        return 0;
    }

    password_len = strlen(password);
    if (password_len == 0 || password_len > MAX_PASSWORD_LEN) {
        return 0;
    }

    /* Find user */
    for (i = 0; i < db->user_count; i++) {
        if (db->users[i].active && strcmp(db->users[i].username, username) == 0) {
            user_creds = &db->users[i];
            break;
        }
    }

    if (user_creds == NULL) {
        /* User not found - perform dummy hash to prevent timing attacks */
        uint8_t dummy_salt[SALT_SIZE] = {0};
        hash_password(password, dummy_salt, computed_hash);
        secure_clear(computed_hash, HASH_SIZE);
        return 0;
    }

    /* Hash provided password with stored salt */
    if (!hash_password(password, user_creds->salt, computed_hash)) {
        secure_clear(computed_hash, HASH_SIZE);
        return 0;
    }

    /* Constant-time comparison - CWE-208 mitigation */
    result = constant_time_compare(computed_hash, user_creds->password_hash, HASH_SIZE);

    /* Securely clear computed hash */
    secure_clear(computed_hash, HASH_SIZE);

    return result;
}

int main(void) {
    UserDatabase db;

    init_database(&db);

    printf("User Authentication System\n");
    printf("==========================\n\n");

    /* Test case 1: Register valid user */
    printf("Test 1: Register user 'alice' with password 'SecurePass123!': ");
    if (register_user(&db, "alice", "SecurePass123!")) {
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }

    /* Test case 2: Authenticate with correct credentials */
    printf("Test 2: Authenticate 'alice' with correct password: ");
    if (authenticate_user(&db, "alice", "SecurePass123!")) {
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }

    /* Test case 3: Authenticate with incorrect password */
    printf("Test 3: Authenticate 'alice' with wrong password: ");
    if (!authenticate_user(&db, "alice", "WrongPassword")) {
        printf("SUCCESS (correctly rejected)\n");
    } else {
        printf("FAILED\n");
    }

    /* Test case 4: Register another user */
    printf("Test 4: Register user 'bob' with password 'AnotherSecure456!': ");
    if (register_user(&db, "bob", "AnotherSecure456!")) {
        printf("SUCCESS\n");
    } else {
        printf("FAILED\n");
    }

    /* Test case 5: Attempt to register duplicate username */
    printf("Test 5: Attempt to register duplicate user 'alice': ");
    if (!register_user(&db, "alice", "DifferentPass789!")) {
        printf("SUCCESS (correctly rejected)\n");
    } else {
        printf("FAILED\n");
    }

    /* Securely clear database before exit */
    secure_clear(&db, sizeof(UserDatabase));

    return 0;
}
