
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sqlite3.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 128
#define SALT_LENGTH 16
#define HASH_LENGTH 32
#define PBKDF2_ITERATIONS 210000
#define MAX_USERNAME_LENGTH 30
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 254
#define MAX_HASH_STRING 256

/* Base64 encoding table */
static const char base64_chars[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/* Base64 encode function */
void base64_encode(const unsigned char* data, size_t len, char* output) {
    size_t i = 0, j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    
    while (len--) {
        char_array_3[i++] = *(data++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for(i = 0; i < 4; i++)
                output[j++] = base64_chars[char_array_4[i]];
            i = 0;
        }
    }
    
    if (i) {
        size_t k;
        for(k = i; k < 3; k++)
            char_array_3[k] = '\0';
        
        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        
        for (k = 0; k < i + 1; k++)
            output[j++] = base64_chars[char_array_4[k]];
        
        while(i++ < 3)
            output[j++] = '=';
    }
    output[j] = '\0';
}

/* Generate cryptographically secure random salt */
int generate_salt(unsigned char* salt, size_t length) {
    if (RAND_bytes(salt, length) != 1) {
        return 0;
    }
    return 1;
}

/* Hash password using PBKDF2-HMAC-SHA256 */
int hash_password(const char* password, const unsigned char* salt, char* output) {
    unsigned char hash[HASH_LENGTH];
    char salt_b64[64];
    char hash_b64[64];
    
    /* Use PBKDF2-HMAC-SHA256 with 210000 iterations */
    if (PKCS5_PBKDF2_HMAC(password, strlen(password),
                          salt, SALT_LENGTH,
                          PBKDF2_ITERATIONS,
                          EVP_sha256(),
                          HASH_LENGTH, hash) != 1) {
        OPENSSL_cleanse(hash, HASH_LENGTH);
        return 0;
    }
    
    /* Encode salt and hash to base64 */
    base64_encode(salt, SALT_LENGTH, salt_b64);
    base64_encode(hash, HASH_LENGTH, hash_b64);
    
    /* Combine as salt:hash */
    snprintf(output, MAX_HASH_STRING, "%s:%s", salt_b64, hash_b64);
    
    /* Clear sensitive data */
    OPENSSL_cleanse(hash, HASH_LENGTH);
    
    return 1;
}

/* Validate username format */
int validate_username(const char* username) {
    regex_t regex;
    int ret;
    
    if (!username || strlen(username) == 0) return 0;
    
    ret = regcomp(&regex, "^[a-zA-Z0-9_]{3,30}$", REG_EXTENDED);
    if (ret != 0) return 0;
    
    ret = regexec(&regex, username, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

/* Validate password strength */
int validate_password(const char* password) {
    size_t len;
    if (!password) return 0;
    len = strlen(password);
    return len >= MIN_PASSWORD_LENGTH && len <= MAX_PASSWORD_LENGTH;
}

/* Validate name format */
int validate_name(const char* name) {
    regex_t regex;
    int ret;
    
    if (!name || strlen(name) == 0) return 0;
    
    ret = regcomp(&regex, "^[a-zA-Z ]{1,50}$", REG_EXTENDED);
    if (ret != 0) return 0;
    
    ret = regexec(&regex, name, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

/* Validate email format */
int validate_email(const char* email) {
    regex_t regex;
    int ret;
    
    if (!email || strlen(email) == 0 || strlen(email) > MAX_EMAIL_LENGTH) return 0;
    
    ret = regcomp(&regex, "^[A-Za-z0-9+_.-]+@[A-Za-z0-9.-]+$", REG_EXTENDED);
    if (ret != 0) return 0;
    
    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    
    return ret == 0;
}

/* Register user with secure password hashing */
const char* register_user(const char* username, const char* password,
                         const char* first_name, const char* last_name,
                         const char* email, const char* db_path) {
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;
    unsigned char salt[SALT_LENGTH];
    char hashed_password[MAX_HASH_STRING];
    int rc;
    const char* result = "Registration failed";
    
    /* Validate all inputs */
    if (!validate_username(username)) {
        return "Invalid input provided";
    }
    if (!validate_password(password)) {
        return "Invalid input provided";
    }
    if (!validate_name(first_name) || !validate_name(last_name)) {
        return "Invalid input provided";
    }
    if (!validate_email(email)) {
        return "Invalid input provided";
    }
    
    /* Generate cryptographically secure salt */
    if (!generate_salt(salt, SALT_LENGTH)) {
        fprintf(stderr, "Failed to generate salt\\n");
        return result;
    }
    
    /* Hash password with salt */
    if (!hash_password(password, salt, hashed_password)) {
        fprintf(stderr, "Password hashing failed\\n");
        OPENSSL_cleanse(salt, SALT_LENGTH);
        return result;
    }
    
    /* Open database connection */
    rc = sqlite3_open(db_path, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to open database: %s\\n", sqlite3_errmsg(db));
        OPENSSL_cleanse(salt, SALT_LENGTH);
        if (db) sqlite3_close(db);
        return result;
    }
    
    /* Begin transaction */
    sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
    
    /* Check if username exists using parameterized query */
    const char* check_sql = "SELECT COUNT(*) FROM users WHERE username = ?";
    rc = sqlite3_prepare_v2(db, check_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\\n", sqlite3_errmsg(db));
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        OPENSSL_cleanse(salt, SALT_LENGTH);
        sqlite3_close(db);
        return result;
    }
    
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        stmt = NULL;
        
        if (count > 0) {
            sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
            OPENSSL_cleanse(salt, SALT_LENGTH);
            sqlite3_close(db);
            return "Username already exists";
        }
    } else {
        sqlite3_finalize(stmt);
        stmt = NULL;
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        OPENSSL_cleanse(salt, SALT_LENGTH);
        sqlite3_close(db);
        return result;
    }
    
    /* Insert new user using parameterized query */
    const char* insert_sql = "INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)";
    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare insert: %s\\n", sqlite3_errmsg(db));
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        OPENSSL_cleanse(salt, SALT_LENGTH);
        sqlite3_close(db);
        return result;
    }
    
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, first_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, last_name, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_TRANSIENT);
    
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        OPENSSL_cleanse(salt, SALT_LENGTH);
        sqlite3_close(db);
        return result;
    }
    
    sqlite3_finalize(stmt);
    sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);
    OPENSSL_cleanse(salt, SALT_LENGTH);
    sqlite3_close(db);
    
    return "Registration succeeded";
}

int main(void) {
    const char* db_path = ":memory:";
    sqlite3* db = NULL;
    
    /* Create test database */
    if (sqlite3_open(db_path, &db) == SQLITE_OK) {
        const char* create_table = 
            "CREATE TABLE users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT UNIQUE NOT NULL, "
            "password_hash TEXT NOT NULL, "
            "first_name TEXT NOT NULL, "
            "last_name TEXT NOT NULL, "
            "email TEXT NOT NULL)";
        sqlite3_exec(db, create_table, NULL, NULL, NULL);
        sqlite3_close(db);
    }
    
    /* Test case 1: Valid registration */
    printf("Test 1: %s\\n", register_user("john_doe", "SecurePass123!", "John", "Doe", 
                                        "john@example.com", db_path));
    
    /* Test case 2: Duplicate username */
    printf("Test 2: %s\\n", register_user("john_doe", "AnotherPass456!", "Jane", "Smith", 
                                        "jane@example.com", db_path));
    
    /* Test case 3: Valid registration with different user */
    printf("Test 3: %s\\n", register_user("jane_smith", "StrongPassword789!", "Jane", "Smith", 
                                        "jane@example.com", db_path));
    
    /* Test case 4: Invalid username (special characters) */
    printf("Test 4: %s\\n", register_user("user@invalid", "Password123!", "Test", "User", 
                                        "test@example.com", db_path));
    
    /* Test case 5: Invalid password (too short) */
    printf("Test 5: %s\\n", register_user("testuser", "short", "Test", "User", 
                                        "test2@example.com", db_path));
    
    return 0;
}
