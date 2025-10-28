
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sqlite3.h>
#include <regex.h>

/* Maximum email length per RFC 5321 */
#define MAX_EMAIL_LENGTH 254
#define MAX_RESULT_LENGTH 256

/**
 * Trims whitespace from both ends of a string in place.
 * 
 * @param str The string to trim
 */
void trim(char* str) {
    if (str == NULL) return;
    
    char* start = str;
    while (isspace((unsigned char)*start)) start++;
    
    if (*start == '\0') {
        str[0] = '\0';
        return;
    }
    
    char* end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;
    
    size_t len = (size_t)(end - start + 1);
    memmove(str, start, len);
    str[len] = '\0';
}

/**
 * Validates email format using POSIX regex.
 * 
 * @param email The email address to validate
 * @return 1 if valid, 0 otherwise
 */
int validateEmail(const char* email) {
    if (email == NULL) return 0;
    
    regex_t regex;
    int ret;
    
    /* Email validation pattern - RFC 5322 simplified */
    const char* pattern = "^[a-zA-Z0-9_+&*-]+(\\\\.[-a-zA-Z0-9_+&*]+)*@([a-zA-Z0-9-]+\\\\.)+[a-zA-Z]{2,7}$";
    
    ret = regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
    if (ret != 0) {
        return 0;
    }
    
    ret = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);
    
    return (ret == 0) ? 1 : 0;
}

/**
 * Unsubscribes an email address from the database.
 * Uses parameterized queries to prevent SQL injection.
 * Validates input before processing.
 * 
 * @param email The email address to unsubscribe
 * @param dbPath Path to the SQLite database file
 * @param result Buffer to store result message (must be at least MAX_RESULT_LENGTH bytes)
 */
void unsubscribe(const char* email, const char* dbPath, char* result) {
    /* Initialize result buffer */
    if (result == NULL) return;
    memset(result, 0, MAX_RESULT_LENGTH);
    
    /* Input validation: NULL or empty check */
    if (email == NULL || strlen(email) == 0) {
        strncpy(result, "Invalid email address provided.", MAX_RESULT_LENGTH - 1);
        return;
    }
    
    /* Create a copy for trimming to avoid modifying input */
    char emailCopy[MAX_EMAIL_LENGTH + 1];
    memset(emailCopy, 0, sizeof(emailCopy));
    strncpy(emailCopy, email, MAX_EMAIL_LENGTH);
    emailCopy[MAX_EMAIL_LENGTH] = '\0';
    trim(emailCopy);
    
    /* Input validation: empty after trim */
    if (strlen(emailCopy) == 0) {
        strncpy(result, "Invalid email address provided.", MAX_RESULT_LENGTH - 1);
        return;
    }
    
    /* Input validation: length check to prevent resource exhaustion */
    if (strlen(emailCopy) > MAX_EMAIL_LENGTH) {
        strncpy(result, "Invalid email address provided.", MAX_RESULT_LENGTH - 1);
        return;
    }
    
    /* Input validation: format check using regex */
    if (!validateEmail(emailCopy)) {
        strncpy(result, "Invalid email address provided.", MAX_RESULT_LENGTH - 1);
        return;
    }
    
    sqlite3* db = NULL;
    sqlite3_stmt* checkStmt = NULL;
    sqlite3_stmt* deleteStmt = NULL;
    int rc;
    
    /* Open database connection */
    rc = sqlite3_open(dbPath, &db);
    if (rc != SQLITE_OK) {
        strncpy(result, "An error occurred while processing your request.", MAX_RESULT_LENGTH - 1);
        if (db != NULL) sqlite3_close(db);
        return;
    }
    
    /* Begin transaction for atomicity */
    rc = sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
    if (rc != SQLITE_OK) {
        strncpy(result, "An error occurred while processing your request.", MAX_RESULT_LENGTH - 1);
        sqlite3_close(db);
        return;
    }
    
    /* Prepare parameterized check query to prevent SQL injection */
    const char* checkQuery = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
    rc = sqlite3_prepare_v2(db, checkQuery, -1, &checkStmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        sqlite3_close(db);
        strncpy(result, "An error occurred while processing your request.", MAX_RESULT_LENGTH - 1);
        return;
    }
    
    /* Bind parameter - prevents SQL injection */
    rc = sqlite3_bind_text(checkStmt, 1, emailCopy, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(checkStmt);
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        sqlite3_close(db);
        strncpy(result, "An error occurred while processing your request.", MAX_RESULT_LENGTH - 1);
        return;
    }
    
    /* Execute check query */
    rc = sqlite3_step(checkStmt);
    int count = 0;
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(checkStmt, 0);
    }
    
    sqlite3_finalize(checkStmt);
    checkStmt = NULL;
    
    if (count == 0) {
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        sqlite3_close(db);
        strncpy(result, "Email address not found in database.", MAX_RESULT_LENGTH - 1);
        return;
    }
    
    /* Prepare parameterized delete query to prevent SQL injection */
    const char* deleteQuery = "DELETE FROM subscribers WHERE email = ?";
    rc = sqlite3_prepare_v2(db, deleteQuery, -1, &deleteStmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        sqlite3_close(db);
        strncpy(result, "An error occurred while processing your request.", MAX_RESULT_LENGTH - 1);
        return;
    }
    
    /* Bind parameter - prevents SQL injection */
    rc = sqlite3_bind_text(deleteStmt, 1, emailCopy, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) {
        sqlite3_finalize(deleteStmt);
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        sqlite3_close(db);
        strncpy(result, "An error occurred while processing your request.", MAX_RESULT_LENGTH - 1);
        return;
    }
    
    /* Execute delete query */
    rc = sqlite3_step(deleteStmt);
    sqlite3_finalize(deleteStmt);
    deleteStmt = NULL;
    
    if (rc == SQLITE_DONE) {
        sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);
        strncpy(result, "Successfully unsubscribed.", MAX_RESULT_LENGTH - 1);
    } else {
        sqlite3_exec(db, "ROLLBACK", NULL, NULL, NULL);
        strncpy(result, "Unsubscribe operation failed.", MAX_RESULT_LENGTH - 1);
    }
    
    sqlite3_close(db);
}

int main(void) {
    /* Create in-memory test database */
    const char* dbPath = ":memory:";
    char result[MAX_RESULT_LENGTH];
    
    sqlite3* db = NULL;
    int rc = sqlite3_open(dbPath, &db);
    
    if (rc == SQLITE_OK) {
        /* Create test table and insert test data */
        sqlite3_exec(db, "CREATE TABLE subscribers (email VARCHAR(254) PRIMARY KEY)", NULL, NULL, NULL);
        sqlite3_exec(db, "INSERT INTO subscribers (email) VALUES ('test1@example.com')", NULL, NULL, NULL);
        sqlite3_exec(db, "INSERT INTO subscribers (email) VALUES ('test2@example.com')", NULL, NULL, NULL);
        sqlite3_exec(db, "INSERT INTO subscribers (email) VALUES ('valid@domain.org')", NULL, NULL, NULL);
        sqlite3_close(db);
        
        /* Test case 1: Valid email that exists in database */
        memset(result, 0, MAX_RESULT_LENGTH);
        unsubscribe("test1@example.com", dbPath, result);
        printf("Test 1: %s\\n", result);
        
        /* Test case 2: Valid email that does not exist in database */
        memset(result, 0, MAX_RESULT_LENGTH);
        unsubscribe("notfound@example.com", dbPath, result);
        printf("Test 2: %s\\n", result);
        
        /* Test case 3: Invalid email format */
        memset(result, 0, MAX_RESULT_LENGTH);
        unsubscribe("invalid-email", dbPath, result);
        printf("Test 3: %s\\n", result);
        
        /* Test case 4: NULL input */
        memset(result, 0, MAX_RESULT_LENGTH);
        unsubscribe(NULL, dbPath, result);
        printf("Test 4: %s\\n", result);
        
        /* Test case 5: SQL injection attempt (should be safely handled) */
        memset(result, 0, MAX_RESULT_LENGTH);
        unsubscribe("test@test.com' OR '1'='1", dbPath, result);
        printf("Test 5: %s\\n", result);
    } else {
        fprintf(stderr, "Test setup failed\\n");
    }
    
    return 0;
}
