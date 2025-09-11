
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_TOKENS 100
#define TOKEN_LENGTH 32
#define SESSION_LENGTH 64

struct TokenEntry {
    char sessionId[SESSION_LENGTH];
    char token[TOKEN_LENGTH * 2 + 1];  // Hex representation
    bool isUsed;
};

struct TokenStore {
    struct TokenEntry entries[MAX_TOKENS];
    int count;
};

static struct TokenStore tokenStore = {{0}, 0};

void generateRandomHex(char* buffer, size_t length) {
    static const char hex_chars[] = "0123456789ABCDEF";
    
    for(size_t i = 0; i < length * 2; i += 2) {
        unsigned char random_byte = (unsigned char)(rand() & 0xFF);
        buffer[i] = hex_chars[random_byte >> 4];
        buffer[i + 1] = hex_chars[random_byte & 0x0F];
    }
    buffer[length * 2] = '\\0';
}

char* generateCSRFToken(const char* sessionId) {
    if(!sessionId || strlen(sessionId) == 0 || strlen(sessionId) >= SESSION_LENGTH) {
        return NULL;
    }
    
    if(tokenStore.count >= MAX_TOKENS) {
        return NULL;
    }
    
    struct TokenEntry* entry = &tokenStore.entries[tokenStore.count++];
    strncpy(entry->sessionId, sessionId, SESSION_LENGTH - 1);
    entry->sessionId[SESSION_LENGTH - 1] = '\\0';
    
    generateRandomHex(entry->token, TOKEN_LENGTH);
    entry->isUsed = false;
    
    return entry->token;
}

bool validateCSRFToken(const char* sessionId, const char* token) {
    if(!sessionId || !token || strlen(sessionId) == 0 || strlen(token) == 0) {
        return false;
    }
    
    for(int i = 0; i < tokenStore.count; i++) {
        if(strcmp(tokenStore.entries[i].sessionId, sessionId) == 0 && 
           strcmp(tokenStore.entries[i].token, token) == 0 &&
           !tokenStore.entries[i].isUsed) {
            tokenStore.entries[i].isUsed = true;  // One-time use token
            return true;
        }
    }
    
    return false;
}

int main() {
    srand((unsigned int)time(NULL));
    
    // Test Case 1: Valid token validation
    const char* sessionId1 = "session123";
    char* token1 = generateCSRFToken(sessionId1);
    printf("Test 1: %d\\n", validateCSRFToken(sessionId1, token1));
    
    // Test Case 2: Invalid token
    const char* sessionId2 = "session456";
    char* token2 = generateCSRFToken(sessionId2);
    printf("Test 2: %d\\n", validateCSRFToken(sessionId2, "invalid_token"));
    
    // Test Case 3: NULL session ID
    printf("Test 3: %d\\n", validateCSRFToken(NULL, "some_token"));
    
    // Test Case 4: Empty token
    const char* sessionId4 = "session789";
    printf("Test 4: %d\\n", validateCSRFToken(sessionId4, ""));
    
    // Test Case 5: Reuse token (should fail)
    const char* sessionId5 = "session101";
    char* token5 = generateCSRFToken(sessionId5);
    validateCSRFToken(sessionId5, token5); // First use
    printf("Test 5: %d\\n", validateCSRFToken(sessionId5, token5));
    
    return 0;
}
