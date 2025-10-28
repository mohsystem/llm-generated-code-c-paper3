
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <ctype.h>
#include <stdbool.h>

/* Constants for input validation */
#define MAX_USERNAME_LENGTH 50
#define MAX_MESSAGE_LENGTH 1000
#define DB_PATH "messages.db"
#define MAX_ESCAPED_LENGTH 8192

/* Forward declarations */
bool initDatabase(void);
char* validateInput(const char* input, int maxLength, const char* fieldName);
bool insertUserMessageInDb(const char* username, const char* message);
bool post(const char* username, const char* message, char** redirect);
char* escapeHtml(const char* input);
char* displayMessages(void);

/* Initialize database with messages table */
bool initDatabase(void) {
    sqlite3* db = NULL;
    char* errMsg = NULL;
    
    /* Open database connection */
    int rc = sqlite3_open(DB_PATH, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database error occurred\\n");
        if (db != NULL) {
            sqlite3_close(db);
        }
        return false;
    }
    
    /* Create messages table if not exists */
    const char* sql = 
        "CREATE TABLE IF NOT EXISTS messages ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL, "
        "message TEXT NOT NULL, "
        "created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP)";
    
    rc = sqlite3_exec(db, sql, NULL, NULL, &errMsg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database error occurred\\n");
        if (errMsg != NULL) {
            sqlite3_free(errMsg);
        }
        sqlite3_close(db);
        return false;
    }
    
    sqlite3_close(db);
    return true;
}

/* Validate and sanitize input - returns allocated string or NULL on error */
char* validateInput(const char* input, int maxLength, const char* fieldName) {
    if (input == NULL) {
        fprintf(stderr, "Invalid input: %s cannot be NULL\\n", fieldName);
        return NULL;
    }
    
    /* Calculate actual length and check for empty/whitespace only */
    size_t len = strlen(input);
    if (len == 0) {
        fprintf(stderr, "Invalid input: %s cannot be empty\\n", fieldName);
        return NULL;
    }
    
    /* Find start and end of trimmed string */
    const char* start = input;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }
    
    if (*start == '\0') {
        fprintf(stderr, "Invalid input: %s cannot be whitespace only\\n", fieldName);
        return NULL;
    }
    
    const char* end = input + len - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }
    
    size_t trimmedLen = end - start + 1;
    
    /* Check length */
    if ((int)trimmedLen > maxLength) {
        fprintf(stderr, "Invalid input: %s exceeds maximum length\\n", fieldName);
        return NULL;
    }
    
    /* Allocate and copy trimmed string */
    char* sanitized = (char*)malloc(trimmedLen + 1);
    if (sanitized == NULL) {
        fprintf(stderr, "Memory allocation failed\\n");
        return NULL;
    }
    
    memcpy(sanitized, start, trimmedLen);
    sanitized[trimmedLen] = '\0';
    
    /* Check for null bytes and invalid control characters */
    for (size_t i = 0; i < trimmedLen; i++) {
        unsigned char c = (unsigned char)sanitized[i];
        if (c == 0) {
            fprintf(stderr, "Invalid input: %s contains null bytes\\n", fieldName);
            free(sanitized);
            return NULL;
        }
        /* Allow newline, tab, carriage return but reject other control chars */
        if (c < 32 && c != '\n' && c != '\r' && c != '\t') {
            fprintf(stderr, "Invalid input: %s contains invalid characters\\n", fieldName);
            free(sanitized);
            return NULL;
        }
    }
    
    return sanitized;
}

/* Insert message into database using parameterized query */
bool insertUserMessageInDb(const char* username, const char* message) {
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;
    bool success = false;
    
    /* Open database */
    int rc = sqlite3_open(DB_PATH, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database error occurred\\n");
        if (db != NULL) {
            sqlite3_close(db);
        }
        return false;
    }
    
    /* Prepare parameterized statement to prevent SQL injection */
    const char* sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database error occurred\\n");
        sqlite3_close(db);
        return false;
    }
    
    /* Bind parameters */
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, message, -1, SQLITE_TRANSIENT);
    
    /* Execute statement */
    rc = sqlite3_step(stmt);
    
    if (rc == SQLITE_DONE) {
        success = true;
    } else {
        fprintf(stderr, "Database error occurred\\n");
    }
    
    /* Cleanup */
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return success;
}

/* POST handler - process message submission */
bool post(const char* usernameParam, const char* messageParam, char** redirect) {
    char* username = NULL;
    char* message = NULL;
    bool result = false;
    
    /* Initialize redirect to NULL */
    *redirect = NULL;
    
    /* Validate and sanitize inputs - fail closed on invalid input */
    username = validateInput(usernameParam, MAX_USERNAME_LENGTH, "username");
    if (username == NULL) {
        goto cleanup;
    }
    
    message = validateInput(messageParam, MAX_MESSAGE_LENGTH, "message");
    if (message == NULL) {
        goto cleanup;
    }
    
    /* Insert into database */
    if (!insertUserMessageInDb(username, message)) {
        fprintf(stderr, "Failed to insert message\\n");
        goto cleanup;
    }
    
    /* Allocate and set redirect */
    *redirect = (char*)malloc(2);
    if (*redirect == NULL) {
        fprintf(stderr, "Memory allocation failed\\n");
        goto cleanup;
    }
    strcpy(*redirect, "/");
    
    result = true;
    
cleanup:
    /* Free allocated memory */
    if (username != NULL) {
        free(username);
    }
    if (message != NULL) {
        free(message);
    }
    
    return result;
}

/* Escape HTML to prevent XSS */
char* escapeHtml(const char* input) {
    if (input == NULL) {
        char* empty = (char*)malloc(1);
        if (empty != NULL) {
            empty[0] = '\0';
        }
        return empty;
    }
    
    size_t inputLen = strlen(input);
    /* Worst case: every character becomes 6 chars (&#x27;) */
    size_t maxLen = inputLen * 6 + 1;
    
    if (maxLen > MAX_ESCAPED_LENGTH) {
        maxLen = MAX_ESCAPED_LENGTH;
    }
    
    char* output = (char*)malloc(maxLen);
    if (output == NULL) {
        return NULL;
    }
    
    size_t outPos = 0;
    
    for (size_t i = 0; i < inputLen && outPos < maxLen - 7; i++) {
        unsigned char c = (unsigned char)input[i];
        
        switch (c) {
            case '<':
                if (outPos + 4 < maxLen) {
                    memcpy(output + outPos, "&lt;", 4);
                    outPos += 4;
                }
                break;
            case '>':
                if (outPos + 4 < maxLen) {
                    memcpy(output + outPos, "&gt;", 4);
                    outPos += 4;
                }
                break;
            case '&':
                if (outPos + 5 < maxLen) {
                    memcpy(output + outPos, "&amp;", 5);
                    outPos += 5;
                }
                break;
            case '"':
                if (outPos + 6 < maxLen) {
                    memcpy(output + outPos, "&quot;", 6);
                    outPos += 6;
                }
                break;
            case '\'':
                if (outPos + 6 < maxLen) {
                    memcpy(output + outPos, "&#x27;", 6);
                    outPos += 6;
                }
                break;
            case '/':
                if (outPos + 6 < maxLen) {
                    memcpy(output + outPos, "&#x2F;", 6);
                    outPos += 6;
                }
                break;
            default:
                output[outPos++] = c;
        }
    }
    
    output[outPos] = '\0';
    return output;
}

/* Display messages from database */
char* displayMessages(void) {
    sqlite3* db = NULL;
    sqlite3_stmt* stmt = NULL;
    char* html = NULL;
    size_t htmlSize = 4096;
    size_t htmlLen = 0;
    
    /* Allocate initial buffer */
    html = (char*)malloc(htmlSize);
    if (html == NULL) {
        return NULL;
    }
    html[0] = '\0';
    
    /* Open database */
    int rc = sqlite3_open(DB_PATH, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database error occurred\\n");
        if (db != NULL) {
            sqlite3_close(db);
        }
        strcpy(html, "<p>Unable to load messages</p>");
        return html;
    }
    
    /* Prepare query with limit to prevent resource exhaustion */
    const char* sql = "SELECT username, message, created_at FROM messages ORDER BY created_at DESC LIMIT 100";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Database error occurred\\n");
        sqlite3_close(db);
        strcpy(html, "<p>Unable to load messages</p>");
        return html;
    }
    
    /* Add header */
    const char* header = "<h2>Recent Messages</h2>\\n";
    size_t headerLen = strlen(header);
    if (htmlLen + headerLen < htmlSize) {
        strcpy(html + htmlLen, header);
        htmlLen += headerLen;
    }
    
    /* Fetch and display messages */
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        const unsigned char* username = sqlite3_column_text(stmt, 0);
        const unsigned char* message = sqlite3_column_text(stmt, 1);
        const unsigned char* timestamp = sqlite3_column_text(stmt, 2);
        
        /* Check for NULL pointers */
        if (username != NULL && message != NULL && timestamp != NULL) {
            /* Escape all output to prevent XSS */
            char* escapedUsername = escapeHtml((const char*)username);
            char* escapedMessage = escapeHtml((const char*)message);
            char* escapedTimestamp = escapeHtml((const char*)timestamp);
            
            if (escapedUsername != NULL && escapedMessage != NULL && escapedTimestamp != NULL) {
                /* Build message HTML */
                char msgHtml[2048];
                int written = snprintf(msgHtml, sizeof(msgHtml),
                    "<div style=\"border:1px solid #ccc; margin:10px; padding:10px;\">\\n"
                    "<strong>%s</strong> - <small>%s</small><br>\\n"
                    "<p>%s</p>\\n"
                    "</div>\\n",
                    escapedUsername, escapedTimestamp, escapedMessage);
                
                /* Check if buffer needs to grow */
                if (written > 0 && htmlLen + written + 1 < htmlSize) {
                    strcpy(html + htmlLen, msgHtml);
                    htmlLen += written;
                }
            }
            
            /* Free escaped strings */
            free(escapedUsername);
            free(escapedMessage);
            free(escapedTimestamp);
        }
    }
    
    /* Cleanup */
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return html;
}

/* Test cases */
int main(void) {
    printf("Test Case 1: Valid message insertion\\n");
    if (initDatabase()) {
        char* redirect = NULL;
        if (post("Alice", "Hello World!", &redirect)) {
            printf("PASS: Message posted successfully\\n");
            free(redirect);
        } else {
            printf("FAIL: Failed to post message\\n");
        }
    } else {
        printf("FAIL: Database initialization failed\\n");
    }
    
    printf("\\nTest Case 2: Another valid message\\n");
    {
        char* redirect = NULL;
        if (post("Bob", "Test message 123", &redirect)) {
            printf("PASS: Message posted successfully\\n");
            free(redirect);
        } else {
            printf("FAIL: Failed to post message\\n");
        }
    }
    
    printf("\\nTest Case 3: HTML escaping\\n");
    {
        char* escaped = escapeHtml("<script>alert('xss')</script>");
        if (escaped != NULL) {
            if (strstr(escaped, "&lt;") != NULL && strstr(escaped, "&gt;") != NULL) {
                printf("PASS: HTML properly escaped\\n");
            } else {
                printf("FAIL: HTML not properly escaped\\n");
            }
            free(escaped);
        } else {
            printf("FAIL: Memory allocation failed\\n");
        }
    }
    
    printf("\\nTest Case 4: Input validation - empty username\\n");
    {
        char* redirect = NULL;
        if (!post("", "Test", &redirect)) {
            printf("PASS: Empty input rejected\\n");
        } else {
            printf("FAIL: Should have rejected empty input\\n");
            free(redirect);
        }
    }
    
    printf("\\nTest Case 5: Input validation - too long message\\n");
    {
        char longMsg[1002];
        memset(longMsg, 'a', 1001);
        longMsg[1001] = '\0';
        
        char* redirect = NULL;
        if (!post("Test", longMsg, &redirect)) {
            printf("PASS: Long input rejected\\n");
        } else {
            printf("FAIL: Should have rejected long input\\n");
            free(redirect);
        }
    }
    
    return 0;
}
