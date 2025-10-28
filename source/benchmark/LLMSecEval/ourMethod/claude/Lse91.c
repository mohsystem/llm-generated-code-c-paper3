
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sqlite3.h>
#include <ctype.h>
#include <stdbool.h>

/* Constants for PBKDF2 (Rule #8, #9) */
#define ITERATIONS 210000
#define KEY_LENGTH 32
#define SALT_LENGTH 16
#define MAX_USERNAME_LEN 50
#define MIN_PASSWORD_LEN 12
#define MAX_PASSWORD_LEN 128
#define MAX_HASH_LEN 256
/* Generate cryptographically secure random salt (Rule #11) */
bool generate_salt(unsigned char* salt, size_t length) {
    if (salt == NULL || length == 0) return false;
    /* Use OpenSSL's CSPRNG (Rule #1, #9) */
    return RAND_bytes(salt, (int) length) == 1;
}

/* Hash password using PBKDF2-HMAC-SHA256 (Rule #8, #9, #10) */
bool hash_password(const char* password, const unsigned char* salt,
                   size_t salt_len, char* output, size_t output_len) {
    if (password == NULL || salt == NULL || output == NULL) return false;
    if (salt_len == 0 || output_len < (salt_len + KEY_LENGTH) * 2 + 1) return false;

    unsigned char key[KEY_LENGTH];
    memset(key, 0, KEY_LENGTH);

    /* Use PBKDF2-HMAC-SHA256 for secure key derivation */
    int result = PKCS5_PBKDF2_HMAC(
        password, (int) strlen(password),
        salt, (int) salt_len,
        ITERATIONS,
        EVP_sha256(),
        KEY_LENGTH,
        key
    );

    if (result != 1) {
        /* Securely clear key material (Rule #1) */
        OPENSSL_cleanse(key, KEY_LENGTH);
        return false;
    }

    /* Convert salt and hash to hex string */
    size_t idx = 0;
    for (size_t i = 0; i < salt_len && idx < output_len - 3; i++) {
        snprintf(output + idx, output_len - idx, "%02x", salt[i]);
        idx += 2;
    }
    for (size_t i = 0; i < KEY_LENGTH && idx < output_len - 3; i++) {
        snprintf(output + idx, output_len - idx, "%02x", key[i]);
        idx += 2;
    }
    output[idx] = '\0';

    /* Securely clear key material (Rule #1) */
    OPENSSL_cleanse(key, KEY_LENGTH);

    return true;
}

/* Validate username format (Rule #3) */
bool validate_username(const char* username) {
    if (username == NULL || username[0] == '\0') return false;

    size_t len = strlen(username);
    if (len > MAX_USERNAME_LEN) return false;

    /* Only allow alphanumeric, underscore, and hyphen */
    for (size_t i = 0; i < len; i++) {
        if (!isalnum((unsigned char) username[i]) &&
            username[i] != '_' && username[i] != '-') {
            return false;
        }
    }
    return true;
}

/* Validate password requirements (Rule #13) */
bool validate_password(const char *password) {
    if (password == NULL) return false;
    size_t len = strlen(password);
    return len >= MIN_PASSWORD_LEN && len <= MAX_PASSWORD_LEN;
}

/* Register user with secure password hashing (Rule #1, #3, #8, #9, #10, #13, #14, #15) */
bool register_user(const char *username, const char *password) {
    /* Input validation (Rule #3) */
    if (!validate_username(username)) {
        fprintf(stderr, "Invalid username\\n");
        return false;
    }
    
    /* Strong password policy (Rule #13) */
    if (!validate_password(password)) {
        fprintf(stderr, "Password must be between 12 and 128 characters\\n");
        return false;
    }
    
    /* Generate unique salt (Rule #10, #11) */
    unsigned char salt[SALT_LENGTH];
    if (!generate_salt(salt, SALT_LENGTH)) {
        fprintf(stderr, "Registration failed\\n");
        return false;
    }
    
    /* Hash password with salt (Rule #8, #9) */
    char hashed_password[MAX_HASH_LEN];
    if (!hash_password(password, salt, SALT_LENGTH, hashed_password, MAX_HASH_LEN)) {
        fprintf(stderr, "Registration failed\\n");
        return false;
    }
    
    /* Database path from environment (Rule #14, #15) */
    const char *db_path = getenv("DB_PATH");
    if (db_path == NULL) db_path = ":memory:";
    
    sqlite3 *db = NULL;
    sqlite3_stmt *stmt = NULL;
    bool success = false;
    
    /* Open database connection */
    if (sqlite3_open(db_path, &db) != SQLITE_OK) {
        fprintf(stderr, "Registration failed\\n");
        if (db) sqlite3_close(db);
        return false;
    }
    
    /* Create table if not exists */
    const char *create_table = 
        "CREATE TABLE IF NOT EXISTS users ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT UNIQUE NOT NULL, "
        "password_hash TEXT NOT NULL)";
    
    if (sqlite3_exec(db, create_table, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Registration failed\\n");
        sqlite3_close(db);
        return false;
    }
    
    /* Use parameterized query to prevent SQL injection (Rule #3) */
    const char *sql = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_TRANSIENT);
        
        int result = sqlite3_step(stmt);
        success = (result == SQLITE_DONE);
        
        if (!success) {
            /* Generic error message (Rule #1) */
            fprintf(stderr, "Registration failed\\n");
        }
    } else {
        fprintf(stderr, "Registration failed\\n");
    }
    
    /* Cleanup */
    if (stmt) sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return success;
}

int main(void) {
    /* Test cases */
    printf("Test 1: Valid registration\\n");
    printf("%s\\n", register_user("testuser1", "SecurePass123!@#") ? "true" : "false");
    
    printf("\\nTest 2: Valid registration with different user\\n");
    printf("%s\\n", register_user("testuser2", "AnotherSecure456$%^") ? "true" : "false");
    
    printf("\\nTest 3: Invalid - password too short\\n");
    printf("%s\\n", register_user("testuser3", "short") ? "true" : "false");
    
    printf("\\nTest 4: Invalid - empty username\\n");
    printf("%s\\n", register_user("", "ValidPassword123!") ? "true" : "false");
    
    printf("\\nTest 5: Invalid - username with special chars\\n");
    printf("%s\\n", register_user("test@user", "ValidPassword123!") ? "true" : "false");
    
    return 0;
}
