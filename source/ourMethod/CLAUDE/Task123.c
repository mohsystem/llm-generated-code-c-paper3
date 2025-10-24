
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

/* Session token length in bytes */
#define TOKEN_LENGTH 32
/* Session timeout in seconds (30 minutes) */
#define SESSION_TIMEOUT 1800
/* Maximum username length */
#define MAX_USERNAME_LENGTH 64
/* Maximum sessions */
#define MAX_SESSIONS 1000
/* Token hex string length */
#define TOKEN_HEX_LENGTH (TOKEN_LENGTH * 2)

typedef struct {
    char username[MAX_USERNAME_LENGTH + 1];
    time_t createdAt;
    time_t lastAccessedAt;
    bool active;
} SessionData;

typedef struct {
    char token[TOKEN_HEX_LENGTH + 1];
    SessionData data;
} Session;

typedef struct {
    Session* sessions;
    size_t count;
    size_t capacity;
} SessionManager;

/* Generate cryptographically secure random bytes using /dev/urandom */
static bool generateSecureRandom(unsigned char* buffer, size_t length) {
    if (buffer == NULL || length == 0) {
        return false;
    }
    
    FILE* urandom = fopen("/dev/urandom", "rb");
    if (urandom == NULL) {
        return false;
    }
    
    size_t read = fread(buffer, 1, length, urandom);
    fclose(urandom);
    
    if (read != length) {
        /* Clear partial data */
        volatile unsigned char* ptr = buffer;
        for (size_t i = 0; i < length; i++) {
            ptr[i] = 0;
        }
        return false;
    }
    
    return true;
}

/* Convert bytes to hex string */
static bool bytesToHex(const unsigned char* data, size_t length, char* output, size_t outputSize) {
    if (data == NULL || output == NULL || outputSize < (length * 2 + 1)) {
        return false;
    }
    
    const char hex_chars[] = "0123456789abcdef";
    
    for (size_t i = 0; i < length; i++) {
        if (i * 2 + 1 >= outputSize) {
            return false;
        }
        output[i * 2] = hex_chars[(data[i] >> 4) & 0x0F];
        output[i * 2 + 1] = hex_chars[data[i] & 0x0F];
    }
    output[length * 2] = '\0';
    
    return true;
}

/* Constant-time string comparison for security */
static bool secureCompare(const char* a, const char* b, size_t length) {
    if (a == NULL || b == NULL) {
        return false;
    }
    
    volatile unsigned char result = 0;
    for (size_t i = 0; i < length; i++) {
        result |= (unsigned char)a[i] ^ (unsigned char)b[i];
    }
    
    return result == 0;
}

/* Validate token format (must be hex string of correct length) */
static bool isValidTokenFormat(const char* token) {
    if (token == NULL) {
        return false;
    }
    
    size_t len = strnlen(token, TOKEN_HEX_LENGTH + 1);
    if (len != TOKEN_HEX_LENGTH) {
        return false;
    }
    
    for (size_t i = 0; i < TOKEN_HEX_LENGTH; i++) {
        char c = token[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) {
            return false;
        }
    }
    
    return true;
}

/* Validate username */
static bool isValidUsername(const char* username) {
    if (username == NULL) {
        return false;
    }
    
    size_t len = strnlen(username, MAX_USERNAME_LENGTH + 1);
    if (len == 0 || len > MAX_USERNAME_LENGTH) {
        return false;
    }
    
    for (size_t i = 0; i < len; i++) {
        char c = username[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || 
              (c >= '0' && c <= '9') || c == '_')) {
            return false;
        }
    }
    
    return true;
}

/* Initialize session manager */
SessionManager* createSessionManager(void) {
    SessionManager* manager = (SessionManager*)calloc(1, sizeof(SessionManager));
    if (manager == NULL) {
        return NULL;
    }
    
    manager->capacity = 100;
    manager->sessions = (Session*)calloc(manager->capacity, sizeof(Session));
    if (manager->sessions == NULL) {
        free(manager);
        return NULL;
    }
    
    manager->count = 0;
    return manager;
}

/* Free session manager */
void destroySessionManager(SessionManager* manager) {
    if (manager == NULL) {
        return;
    }
    
    if (manager->sessions != NULL) {
        /* Clear sensitive data before freeing */
        volatile char* ptr = (volatile char*)manager->sessions;
        size_t size = manager->capacity * sizeof(Session);
        for (size_t i = 0; i < size; i++) {
            ptr[i] = 0;
        }
        free(manager->sessions);
    }
    
    free(manager);
}

/* Create new session */
bool createSession(SessionManager* manager, const char* username, char* tokenOut, size_t tokenOutSize) {
    if (manager == NULL || username == NULL || tokenOut == NULL || tokenOutSize < TOKEN_HEX_LENGTH + 1) {
        return false;
    }
    
    /* Validate username */
    if (!isValidUsername(username)) {
        return false;
    }
    
    /* Check session limit */
    if (manager->count >= MAX_SESSIONS) {
        return false;
    }
    
    /* Generate secure random token */
    unsigned char tokenBytes[TOKEN_LENGTH];
    if (!generateSecureRandom(tokenBytes, TOKEN_LENGTH)) {
        return false;
    }
    
    char token[TOKEN_HEX_LENGTH + 1];
    if (!bytesToHex(tokenBytes, TOKEN_LENGTH, token, sizeof(token))) {
        /* Clear token bytes */
        volatile unsigned char* ptr = tokenBytes;
        for (size_t i = 0; i < TOKEN_LENGTH; i++) {
            ptr[i] = 0;
        }
        return false;
    }
    
    /* Clear token bytes from memory */
    volatile unsigned char* ptr = tokenBytes;
    for (size_t i = 0; i < TOKEN_LENGTH; i++) {
        ptr[i] = 0;
    }
    
    time_t now = time(NULL);
    if (now == (time_t)(-1)) {
        return false;
    }
    
    /* Expand capacity if needed */
    if (manager->count >= manager->capacity) {
        size_t newCapacity = manager->capacity * 2;
        if (newCapacity > MAX_SESSIONS) {
            newCapacity = MAX_SESSIONS;
        }
        
        Session* newSessions = (Session*)realloc(manager->sessions, newCapacity * sizeof(Session));
        if (newSessions == NULL) {
            return false;
        }
        
        manager->sessions = newSessions;
        manager->capacity = newCapacity;
    }
    
    /* Add session */
    Session* session = &manager->sessions[manager->count];
    strncpy(session->token, token, TOKEN_HEX_LENGTH);
    session->token[TOKEN_HEX_LENGTH] = '\0';
    
    strncpy(session->data.username, username, MAX_USERNAME_LENGTH);
    session->data.username[MAX_USERNAME_LENGTH] = '\0';
    
    session->data.createdAt = now;
    session->data.lastAccessedAt = now;
    session->data.active = true;
    
    manager->count++;
    
    /* Copy token to output */
    strncpy(tokenOut, token, tokenOutSize - 1);
    tokenOut[tokenOutSize - 1] = '\0';
    
    return true;
}

/* Validate session */
bool validateSession(SessionManager* manager, const char* token) {
    if (manager == NULL || !isValidTokenFormat(token)) {
        return false;
    }
    
    time_t now = time(NULL);
    if (now == (time_t)(-1)) {
        return false;
    }
    
    for (size_t i = 0; i < manager->count; i++) {
        Session* session = &manager->sessions[i];
        
        if (session->data.active && 
            secureCompare(session->token, token, TOKEN_HEX_LENGTH)) {
            
            /* Check timeout */
            if (now - session->data.lastAccessedAt > SESSION_TIMEOUT) {
                session->data.active = false;
                return false;
            }
            
            /* Update last accessed time */
            session->data.lastAccessedAt = now;
            return true;
        }
    }
    
    return false;
}

/* Get username for session */
bool getUsername(SessionManager* manager, const char* token, char* usernameOut, size_t usernameOutSize) {
    if (manager == NULL || token == NULL || usernameOut == NULL || usernameOutSize == 0) {
        return false;
    }
    
    if (!validateSession(manager, token)) {
        return false;
    }
    
    for (size_t i = 0; i < manager->count; i++) {
        Session* session = &manager->sessions[i];
        
        if (session->data.active && 
            secureCompare(session->token, token, TOKEN_HEX_LENGTH)) {
            
            strncpy(usernameOut, session->data.username, usernameOutSize - 1);
            usernameOut[usernameOutSize - 1] = '\0';
            return true;
        }
    }
    
    return false;
}

/* Destroy session */
bool destroySession(SessionManager* manager, const char* token) {
    if (manager == NULL || !isValidTokenFormat(token)) {
        return false;
    }
    
    for (size_t i = 0; i < manager->count; i++) {
        Session* session = &manager->sessions[i];
        
        if (secureCompare(session->token, token, TOKEN_HEX_LENGTH)) {
            session->data.active = false;
            
            /* Clear sensitive data */
            volatile char* ptr = (volatile char*)&session->data;
            for (size_t j = 0; j < sizeof(SessionData); j++) {
                ptr[j] = 0;
            }
            
            return true;
        }
    }
    
    return false;
}

int main(void) {
    SessionManager* manager = createSessionManager();
    if (manager == NULL) {
        printf("Failed to create session manager\n");
        return 1;
    }
    
    /* Test case 1: Create valid session */
    printf("Test 1: Create valid session\n");
    char token1[TOKEN_HEX_LENGTH + 1];
    if (createSession(manager, "user_alice", token1, sizeof(token1))) {
        printf("PASS: Session created with token length: %zu\n", strlen(token1));
    } else {
        printf("FAIL: Session creation failed\n");
    }
    
    /* Test case 2: Validate existing session */
    printf("\nTest 2: Validate existing session\n");
    if (validateSession(manager, token1)) {
        char username[MAX_USERNAME_LENGTH + 1];
        if (getUsername(manager, token1, username, sizeof(username))) {
            if (strcmp(username, "user_alice") == 0) {
                printf("PASS: Session validated, username: %s\n", username);
            } else {
                printf("FAIL: Username mismatch\n");
            }
        } else {
            printf("FAIL: Failed to get username\n");
        }
    } else {
        printf("FAIL: Session validation failed\n");
    }
    
    /* Test case 3: Reject invalid token format */
    printf("\nTest 3: Reject invalid token\n");
    if (!validateSession(manager, "invalid_token_123")) {
        printf("PASS: Invalid token rejected\n");
    } else {
        printf("FAIL: Invalid token accepted\n");
    }
    
    /* Test case 4: Destroy session */
    printf("\nTest 4: Destroy session\n");
    if (destroySession(manager, token1)) {
        if (!validateSession(manager, token1)) {
            printf("PASS: Session destroyed successfully\n");
        } else {
            printf("FAIL: Session still valid after destroy\n");
        }
    } else {
        printf("FAIL: Session destroy failed\n");
    }
    
    /* Test case 5: Invalid username rejection */
    printf("\nTest 5: Reject invalid username\n");
    char token2[TOKEN_HEX_LENGTH + 1];
    if (!createSession(manager, "user@invalid!", token2, sizeof(token2))) {
        printf("PASS: Invalid username rejected\n");
    } else {
        printf("FAIL: Invalid username accepted\n");
    }
    
    destroySessionManager(manager);
    return 0;
}
