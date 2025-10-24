
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>

/* Security: Use PBKDF2 for password hashing with unique salt per user */
/* Security: Validate all inputs to prevent injection and buffer overflow */
/* Security: Use constant-time comparison for password verification */
/* Security: Clear sensitive data from memory after use */

#define SALT_SIZE 16
#define HASH_SIZE 32
#define PBKDF2_ITERATIONS 210000
#define MAX_NAME_LEN 100
#define MAX_EMAIL_LEN 254
#define MAX_PASSWORD_LEN 128
#define MAX_USERS 1000

typedef struct {
    char name[MAX_NAME_LEN + 1];
    char email[MAX_EMAIL_LEN + 1];
    unsigned char salt[SALT_SIZE];
    unsigned char password_hash[HASH_SIZE];
} User;

typedef struct {
    User users[MAX_USERS];
    size_t user_count;
    char db_file[256];
} UserDatabase;

/* Security: Validate name - alphanumeric, spaces, basic punctuation only */
int validate_name(const char* name) {
    if (name == NULL) return 0;
    
    size_t len = strlen(name);
    if (len == 0 || len > MAX_NAME_LEN) return 0;

    for (size_t i = 0; i < len; i++) {
        char c = name[i];
        if (!isalnum(c) && c != ' ' && c != '.' && c != '\'' && c != '-') {
            return 0;
        }
    }
    return 1;
}

/* Security: Validate email format using basic rules */
int validate_email(const char* email) {
    if (email == NULL) return 0;
    
    size_t len = strlen(email);
    if (len == 0 || len > MAX_EMAIL_LEN) return 0;

    /* Security: Check for @ symbol and basic structure */
    const char* at = strchr(email, '@');
    if (at == NULL || at == email || at == email + len - 1) return 0;

    const char* dot = strchr(at, '.');
    if (dot == NULL || dot == at + 1 || dot >= email + len - 1) return 0;

    /* Security: Validate allowed characters */
    for (size_t i = 0; i < len; i++) {
        char c = email[i];
        if (!isalnum(c) && c != '@' && c != '.' && c != '_' && 
            c != '%' && c != '+' && c != '-') {
            return 0;
        }
    }
    return 1;
}

/* Security: Validate password requirements */
int validate_password(const char* password) {
    if (password == NULL) return 0;
    
    size_t len = strlen(password);
    /* Security: Enforce strong password policy */
    if (len < 12 || len > MAX_PASSWORD_LEN) return 0;

    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    for (size_t i = 0; i < len; i++) {
        if (isupper(password[i])) has_upper = 1;
        else if (islower(password[i])) has_lower = 1;
        else if (isdigit(password[i])) has_digit = 1;
        else if (ispunct(password[i])) has_special = 1;
    }
    return has_upper && has_lower && has_digit && has_special;
}
/* Security: Generate cryptographically secure random salt */
int generate_salt(unsigned char *salt, size_t size) {
    if (salt == NULL || size != SALT_SIZE) return 0;

    /* Security: Use OpenSSL's CSPRNG for salt generation */
    if (RAND_bytes(salt, size) != 1) {
        return 0;
    }
    return 1;
}

/* Security: Hash password using PBKDF2-HMAC-SHA256 */
int hash_password(const char *password, const unsigned char *salt,
                  unsigned char *hash) {
    if (password == NULL || salt == NULL || hash == NULL) return 0;

    size_t password_len = strlen(password);
    if (password_len == 0 || password_len > MAX_PASSWORD_LEN) return 0;

    /* Security: Use PBKDF2 with 210,000 iterations as per OWASP guidelines */
    if (PKCS5_PBKDF2_HMAC(password, password_len,
                          salt, SALT_SIZE,
                          PBKDF2_ITERATIONS,
                          EVP_sha256(),
                          HASH_SIZE,
                          hash) != 1) {
        return 0;
    }
    return 1;
}

/* Security: Constant-time comparison to prevent timing attacks */
int constant_time_compare(const unsigned char *a, const unsigned char *b,
                          size_t size) {
    if (a == NULL || b == NULL) return 0;
    return CRYPTO_memcmp(a, b, size) == 0;
}

/* Security: Clear sensitive data from memory */
void secure_clear(void *ptr, size_t size) {
    if (ptr != NULL && size > 0) {
        OPENSSL_cleanse(ptr, size);
    }
}

void bytes_to_hex(const unsigned char *bytes, size_t len, char *hex) {
    if (bytes == NULL || hex == NULL) return;

    /* Security: Bounds check for hex buffer */
    for (size_t i = 0; i < len; i++) {
        snprintf(hex + (i * 2), 3, "%02x", bytes[i]);
    }
}

void hex_to_bytes(const char *hex, unsigned char *bytes, size_t byte_len) {
    if (hex == NULL || bytes == NULL) return;

    /* Security: Validate hex string length */
    size_t hex_len = strlen(hex);
    if (hex_len != byte_len * 2) return;

    for (size_t i = 0; i < byte_len; i++) {
        char byte_str[3] = { hex[i * 2], hex[i * 2 + 1], '\0' };
        bytes[i] = (unsigned char)strtol(byte_str, NULL, 16);
    }
}

UserDatabase *create_database(const char *filename) {
    if (filename == NULL) return NULL;

    UserDatabase *db = (UserDatabase *)calloc(1, sizeof(UserDatabase));
    if (db == NULL) return NULL;

    /* Security: Bounds check for filename */
    strncpy(db->db_file, filename, sizeof(db->db_file) - 1);
    db->db_file[sizeof(db->db_file) - 1] = '\0';
    db->user_count = 0;

    return db;
}

void save_to_file(const UserDatabase *db) {
    if (db == NULL) return;

    FILE *file = fopen(db->db_file, "w");
    if (file == NULL) return;

    for (size_t i = 0; i < db->user_count; i++) {
        char salt_hex[SALT_SIZE * 2 + 1];
        char hash_hex[HASH_SIZE * 2 + 1];

        bytes_to_hex(db->users[i].salt, SALT_SIZE, salt_hex);
        salt_hex[SALT_SIZE * 2] = '\0';

        bytes_to_hex(db->users[i].password_hash, HASH_SIZE, hash_hex);
        hash_hex[HASH_SIZE * 2] = '\0';

        /* Security: Store only non-sensitive data and hashed passwords */
        fprintf(file, "%s|%s|%s|%s\n",
                db->users[i].name,
                db->users[i].email,
                salt_hex,
                hash_hex);
    }
    fclose(file);
}

void load_from_file(UserDatabase *db) {
    if (db == NULL) return;

    FILE *file = fopen(db->db_file, "r");
    if (file == NULL) return;

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL &&
           db->user_count < MAX_USERS) {
        /* Security: Bounds check for line buffer */
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char name[MAX_NAME_LEN + 1] = {0};
        char email[MAX_EMAIL_LEN + 1] = {0};
        char salt_hex[SALT_SIZE * 2 + 1] = {0};
        char hash_hex[HASH_SIZE * 2 + 1] = {0};

        /* Security: Use safe parsing with bounds */
        char *token = strtok(line, "|");
        if (token != NULL) {
            strncpy(name, token, MAX_NAME_LEN);
            name[MAX_NAME_LEN] = '\0';
        }

        token = strtok(NULL, "|");
        if (token != NULL) {
            strncpy(email, token, MAX_EMAIL_LEN);
            email[MAX_EMAIL_LEN] = '\0';
        }

        token = strtok(NULL, "|");
        if (token != NULL) {
            strncpy(salt_hex, token, SALT_SIZE * 2);
            salt_hex[SALT_SIZE * 2] = '\0';
        }

        token = strtok(NULL, "|");
        if (token != NULL) {
            strncpy(hash_hex, token, HASH_SIZE * 2);
            hash_hex[HASH_SIZE * 2] = '\0';
        }

        /* Security: Validate loaded data */
        if (validate_name(name) && validate_email(email)) {
            User *user = &db->users[db->user_count];
            strncpy(user->name, name, MAX_NAME_LEN);
            user->name[MAX_NAME_LEN] = '\0';
            strncpy(user->email, email, MAX_EMAIL_LEN);
            user->email[MAX_EMAIL_LEN] = '\0';

            hex_to_bytes(salt_hex, user->salt, SALT_SIZE);
            hex_to_bytes(hash_hex, user->password_hash, HASH_SIZE);

            db->user_count++;
        }
    }
    fclose(file);
}

/* Security: Register user with validated inputs and secure password storage */
int register_user(UserDatabase *db, const char *name, const char *email,
                  const char *password, char *error_msg, size_t error_len) {
    if (db == NULL || name == NULL || email == NULL ||
        password == NULL || error_msg == NULL) {
        return 0;
    }

    /* Security: Validate all inputs before processing */
    if (!validate_name(name)) {
        strncpy(error_msg, "Invalid name format", error_len - 1);
        error_msg[error_len - 1] = '\0';
        return 0;
    }

    if (!validate_email(email)) {
        strncpy(error_msg, "Invalid email format", error_len - 1);
        error_msg[error_len - 1] = '\0';
        return 0;
    }

    if (!validate_password(password)) {
        strncpy(error_msg, "Weak password", error_len - 1);
        error_msg[error_len - 1] = '\0';
        return 0;
    }

    /* Security: Check for duplicate email */
    for (size_t i = 0; i < db->user_count; i++) {
        if (strcmp(db->users[i].email, email) == 0) {
            strncpy(error_msg, "Email already registered", error_len - 1);
            error_msg[error_len - 1] = '\0';
            return 0;
        }
    }

    /* Security: Check database capacity */
    if (db->user_count >= MAX_USERS) {
        strncpy(error_msg, "Database full", error_len - 1);
        error_msg[error_len - 1] = '\0';
        return 0;
    }

    User *new_user = &db->users[db->user_count];

    strncpy(new_user->name, name, MAX_NAME_LEN);
    new_user->name[MAX_NAME_LEN] = '\0';
    strncpy(new_user->email, email, MAX_EMAIL_LEN);
    new_user->email[MAX_EMAIL_LEN] = '\0';

    /* Security: Generate unique salt for this user */
    if (!generate_salt(new_user->salt, SALT_SIZE)) {
        strncpy(error_msg, "Failed to generate salt", error_len - 1);
        error_msg[error_len - 1] = '\0';
        return 0;
    }

    /* Security: Hash password with salt */
    if (!hash_password(password, new_user->salt, new_user->password_hash)) {
        strncpy(error_msg, "Failed to hash password", error_len - 1);
        error_msg[error_len - 1] = '\0';
        return 0;
    }

    db->user_count++;
    save_to_file(db);

    strncpy(error_msg, "User registered successfully", error_len - 1);
    error_msg[error_len - 1] = '\0';
    return 1;
}


/* Security: Verify password with constant-time comparison */
int verify_user(const UserDatabase* db, const char* email, 
                const char* password) {
    if (db == NULL || email == NULL || password == NULL) return 0;

    /* Security: Validate inputs */
    if (!validate_email(email)) return 0;

    for (size_t i = 0; i < db->user_count; i++) {
        if (strcmp(db->users[i].email, email) == 0) {
            unsigned char computed_hash[HASH_SIZE];
            
            if (!hash_password(password, db->users[i].salt, computed_hash)) {
                /* Security: Clear sensitive data */
                secure_clear(computed_hash, HASH_SIZE);
                return 0;
            }
            
            /* Security: Use constant-time comparison */
            int result = constant_time_compare(db->users[i].password_hash, 
                                              computed_hash, HASH_SIZE);
            
            /* Security: Clear sensitive data */
            secure_clear(computed_hash, HASH_SIZE);
            return result;
        }
    }
    return 0;
}

void free_database(UserDatabase* db) {
    if (db == NULL) return;
    
    /* Security: Clear sensitive data before freeing */
    secure_clear(db, sizeof(UserDatabase));
    free(db);
}

int main(void) {
    /* Security: Initialize OpenSSL */
    OpenSSL_add_all_algorithms();

    UserDatabase* db = create_database("users.db");
    if (db == NULL) {
        fprintf(stderr, "Failed to create database\n");
        return 1;
    }

    load_from_file(db);

    char error[256];

    /* Test case 1: Valid registration */
    int result = register_user(db, "John Doe", "john@example.com", 
                               "SecurePass123!", error, sizeof(error));
    printf("Test 1 - Valid registration: %s - %s\n",
           result ? "SUCCESS" : "FAILED", error);

    /* Test case 2: Weak password */
    result = register_user(db, "Jane Smith", "jane@example.com", 
                          "weak", error, sizeof(error));
    printf("Test 2 - Weak password: %s - %s\n",
           !result ? "SUCCESS" : "FAILED", error);

    /* Test case 3: Invalid email */
    result = register_user(db, "Bob Wilson", "invalid-email", 
                          "StrongPass456!", error, sizeof(error));
    printf("Test 3 - Invalid email: %s - %s\n",
           !result ? "SUCCESS" : "FAILED", error);

    /* Test case 4: Duplicate email */
    result = register_user(db, "John Clone", "john@example.com", 
                          "AnotherPass789!", error, sizeof(error));
    printf("Test 4 - Duplicate email: %s - %s\n",
           !result ? "SUCCESS" : "FAILED", error);

    /* Test case 5: Password verification */
    int verified = verify_user(db, "john@example.com", "SecurePass123!");
    printf("Test 5 - Password verification: %s\n",
           verified ? "SUCCESS" : "FAILED");

    printf("\nTotal users registered: %zu\n", db->user_count);

    /* Security: Clean up */
    free_database(db);
    EVP_cleanup();

    return 0;
}
