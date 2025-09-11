
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SESSIONS 100
#define TOKEN_LENGTH 32
#define MAX_TOKEN_STR_LENGTH (TOKEN_LENGTH * 2 + 1)

struct TokenEntry {
    char sessionId[64];
    char token[MAX_TOKEN_STR_LENGTH];
};

struct CSRFProtection {
    struct TokenEntry tokenStore[MAX_SESSIONS];
    int tokenCount;
};

void initCSRFProtection(struct CSRFProtection* csrf) {
    csrf->tokenCount = 0;
    srand(time(NULL));
}

void generateRandomHex(char* buffer, size_t length) {
    const char hex_chars[] = "0123456789ABCDEF";
    for(size_t i = 0; i < length; i++) {
        buffer[i] = hex_chars[rand() % 16];
    }
    buffer[length] = '\\0';
}

char* generateToken(struct CSRFProtection* csrf, const char* sessionId) {
    if(csrf->tokenCount >= MAX_SESSIONS) {
        return NULL;
    }
    
    struct TokenEntry* entry = &csrf->tokenStore[csrf->tokenCount++];
    strncpy(entry->sessionId, sessionId, sizeof(entry->sessionId) - 1);
    entry->sessionId[sizeof(entry->sessionId) - 1] = '\\0';
    
    generateRandomHex(entry->token, TOKEN_LENGTH);
    return entry->token;
}

bool validateToken(struct CSRFProtection* csrf, const char* sessionId, const char* receivedToken) {
    if(!sessionId || !receivedToken) {
        return false;
    }
    
    for(int i = 0; i < csrf->tokenCount; i++) {
        if(strcmp(csrf->tokenStore[i].sessionId, sessionId) == 0) {
            return strcmp(csrf->tokenStore[i].token, receivedToken) == 0;
        }
    }
    
    return false;
}

void setCSRFCookie(char* response, size_t response_size, const char* token) {
    snprintf(response, response_size,
             "Set-Cookie: CSRF-TOKEN=%s; HttpOnly; Secure; SameSite=Strict; Path=/\\r\\n",
             token);
}

int main() {
    struct CSRFProtection csrf;
    initCSRFProtection(&csrf);
    
    // Test Case 1: Generate and validate valid token
    const char* sessionId1 = "session1";
    char* token1 = generateToken(&csrf, sessionId1);
    printf("Test 1 - Valid token: %d\\n", 
           token1 && validateToken(&csrf, sessionId1, token1));
    
    // Test Case 2: Invalid token
    printf("Test 2 - Invalid token: %d\\n",
           validateToken(&csrf, sessionId1, "invalid_token"));
    
    // Test Case 3: Missing token
    printf("Test 3 - Missing token: %d\\n",
           validateToken(&csrf, sessionId1, NULL));
    
    // Test Case 4: Different session
    const char* sessionId2 = "session2";
    char* token2 = generateToken(&csrf, sessionId2);
    printf("Test 4 - Wrong session: %d\\n",
           validateToken(&csrf, sessionId1, token2));
    
    // Test Case 5: Generate multiple tokens
    char* token3 = generateToken(&csrf, sessionId1);
    char* token4 = generateToken(&csrf, sessionId1);
    printf("Test 5 - Tokens different: %d\\n",
           token3 && token4 && strcmp(token3, token4) != 0);
    
    return 0;
}
