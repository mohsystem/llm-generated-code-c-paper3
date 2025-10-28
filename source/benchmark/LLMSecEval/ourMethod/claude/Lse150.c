
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sqlite3.h>
#include <stdbool.h>

/* Maximum input lengths to prevent buffer overflow */
#define MAX_USERNAME_LENGTH 50
#define MAX_MESSAGE_LENGTH 500

/**
 * Validates input string with strict bounds checking.
 * Ensures null termination and rejects control characters.
 * 
 * @param input The input string to validate (must be null-terminated)
 * @param max_length Maximum allowed length
 * @return true if valid, false otherwise
 */
bool validate_input(const char* input, size_t max_length) {
    size_t len;
    size_t i;
    
    /* Check for NULL pointer - fail closed */
    if (input == NULL) {
        return false;
    }
    
    /* Use strnlen to safely check length with boundary */
    len = strnlen(input, max_length + 1);
    
    /* Check if string exceeds maximum length */
    if (len > max_length || len == 0) {
        return false;
    }
    
    /* Validate each character - reject control characters except newline/tab */
    for (i = 0; i < len; i++) {
        if (iscntrl((unsigned char)input[i]) && 
            input[i] != '\n' && input[i] != '\t') {
            return false;
        }
    }
    
    /* Verify null termination within bounds */
    if (input[len] != '\0') {
        return false;
    }
    
    return true;
}

/**
 * Inserts user message into database using parameterized statements
 * to prevent SQL injection attacks.
 * 
 * @param username Validated username (must be null-terminated)
 * @param message Validated message (must be null-terminated)
 * @return true if successful, false otherwise
 */
bool insert_user_message_in_db(const char* username, const char* message) {
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;
    int rc;
    bool success = false;
    
    /* Check for NULL pointers before proceeding */
    if (username == NULL || message == NULL) {
        fprintf(stderr, "Database error occurred\\n");
        return false;
    }
    
    /* Open database connection */
    rc = sqlite3_open("messages.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database error occurred\\n");
        if (db != NULL) {
            sqlite3_close(db);
        }
        return false;
    }
    
    /* Create table if not exists */
    const char* create_table = 
        "CREATE TABLE IF NOT EXISTS messages ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL, "
        "message TEXT NOT NULL, "
        "timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)";
    
    rc = sqlite3_exec(db, create_table, NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database error occurred\\n");
        sqlite3_close(db);
        return false;
    }
    
    /* Use parameterized query to prevent SQL injection */
    const char* sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database error occurred\\n");
        sqlite3_close(db);
        return false;
    }
    
    /* Bind parameters - SQLite handles escaping automatically */
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, message, -1, SQLITE_TRANSIENT);
    
    /* Execute statement */
    rc = sqlite3_step(stmt);
    success = (rc == SQLITE_DONE);
    
    /* Cleanup - finalize statement and close database */
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    if (!success) {
        fprintf(stderr, "Database error occurred\\n");
    }
    
    return success;
}

/**
 * Handles POST request for message submission.
 * Validates all inputs and uses secure database operations.
 * 
 * @param username_param Raw username from request (must be null-terminated)
 * @param message_param Raw message from request (must be null-terminated)
 * @return HTTP status code
 */
int post(const char* username_param, const char* message_param) {
    /* Treat input as untrusted - check for NULL pointers */
    if (username_param == NULL || message_param == NULL) {
        printf("HTTP/1.1 400 Bad Request\\r\\n");
        printf("X-Content-Type-Options: nosniff\\r\\n");
        printf("X-Frame-Options: DENY\\r\\n");
        printf("Content-Security-Policy: default-src 'self'\\r\\n\\r\\n");
        printf("Invalid input\\n");
        return 400;
    }
    
    /* Validate inputs with strict bounds checking */
    if (!validate_input(username_param, MAX_USERNAME_LENGTH) || 
        !validate_input(message_param, MAX_MESSAGE_LENGTH)) {
        /* Fail closed with generic error message */
        printf("HTTP/1.1 400 Bad Request\\r\\n");
        printf("X-Content-Type-Options: nosniff\\r\\n");
        printf("X-Frame-Options: DENY\\r\\n");
        printf("Content-Security-Policy: default-src 'self'\\r\\n\\r\\n");
        printf("Invalid input\\n");
        return 400;
        }
    
    /* Insert into database using parameterized query */
    bool success = insert_user_message_in_db(username_param, message_param);
    
    if (!success) {
        /* Generic error - don't expose database details */
        printf("HTTP/1.1 500 Internal Server Error\r\n");
        printf("X-Content-Type-Options: nosniff\r\n");
        printf("X-Frame-Options: DENY\r\n");
        printf("Content-Security-Policy: default-src 'self'\r\n\r\n");
        printf("Error processing request\n");
        return 500;

        /* Redirect to main page - use absolute path to prevent open redirect */
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: /index.html\r\n");
        printf("X-Content-Type-Options: nosniff\r\n");
        printf("X-Frame-Options: DENY\r\n");
        printf("Content-Security-Policy: default-src 'self'\r\n\r\n");

        return 302;
    }
}
    /* Test cases */
    int main(void) {
        printf("Test 1: Valid input validation\n");
        bool result1 = validate_input("testuser", MAX_USERNAME_LENGTH);
        printf("Result: %s\n", result1 ? "PASS" : "FAIL");

        printf("\nTest 2: Empty input validation\n");
        bool result2 = validate_input("", MAX_USERNAME_LENGTH);
        printf("Result: %s\n", !result2 ? "PASS" : "FAIL");

        printf("\nTest 3: NULL input validation\n");
        bool result3 = validate_input(NULL, MAX_USERNAME_LENGTH);
        printf("Result: %s\n", !result3 ? "PASS" : "FAIL");

        printf("\nTest 4: Exceeds max length validation\n");
        char long_input[MAX_USERNAME_LENGTH + 2];
        memset(long_input, 'a', MAX_USERNAME_LENGTH + 1);
        long_input[MAX_USERNAME_LENGTH + 1] = '\0';
        bool result4 = validate_input(long_input, MAX_USERNAME_LENGTH);
    printf("Result: %s\\n", !result4 ? "PASS" : "FAIL");
    
    printf("\\nTest 5: Input with null byte\\n");
    char null_input[] = "test\\0user";
    bool result5 = validate_input(null_input, MAX_USERNAME_LENGTH);
    printf("Result: %s\\n", !result5 ? "PASS" : "FAIL");
    
    return 0;
}
