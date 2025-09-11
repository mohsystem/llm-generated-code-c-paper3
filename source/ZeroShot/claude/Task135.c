
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define TOKEN_LENGTH 32
#define MAX_SESSIONS 100

typedef struct {
    char sessionId[64];
    char token[TOKEN_LENGTH + 1];
} TokenEntry;

static TokenEntry tokenStore[MAX_SESSIONS];
static int tokenCount = 0;
static const char CHARS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

void generateToken(const char* sessionId, char* token) {
    int i;
    if(tokenCount >= MAX_SESSIONS) {
        token[0] = '\\0';
        return;
    }
    
    for(i = 0; i < TOKEN_LENGTH; i++) {
        token[i] = CHARS[rand() % (sizeof(CHARS) - 1)];
    }
    token[TOKEN_LENGTH] = '\\0';
    
    // Store token
    strcpy(tokenStore[tokenCount].sessionId, sessionId);
    strcpy(tokenStore[tokenCount].token, token);
    tokenCount++;
}

bool validateToken(const char* sessionId, const char* token) {
    if(!sessionId || !token) {
        return false;
    }
    
    for(int i = 0; i < tokenCount; i++) {
        if(strcmp(tokenStore[i].sessionId, sessionId) == 0) {
            return strcmp(tokenStore[i].token, token) == 0;
        }
    }
    return false;
}

int main() {
    srand(time(NULL));
    char token[TOKEN_LENGTH + 1];
    
    // Test case 1: Generate and validate valid token
    generateToken("session123", token);
    printf("Test 1: %d\\n", validateToken("session123", token));

    // Test case 2: Invalid token
    printf("Test 2: %d\\n", validateToken("session123", "wrongtoken"));

    // Test case 3: Invalid session ID
    printf("Test 3: %d\\n", validateToken("wrongsession", token));

    // Test case 4: NULL values
    printf("Test 4: %d\\n", validateToken(NULL, token));

    // Test case 5: Generate new token for same session
    char newToken[TOKEN_LENGTH + 1];
    generateToken("session123", newToken);
    printf("Test 5: %d\\n", validateToken("session123", token));

    return 0;
}
