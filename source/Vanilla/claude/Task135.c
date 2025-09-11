
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_TOKENS 100
#define TOKEN_LENGTH 32
#define SESSION_LENGTH 32

struct CSRFToken {
    char session_id[SESSION_LENGTH];
    char token[TOKEN_LENGTH];
};

struct CSRFToken token_store[MAX_TOKENS];
int token_count = 0;

void generate_random_string(char *str, int length) {
    static const char charset[] = "0123456789"
                                "abcdefghijklmnopqrstuvwxyz"
                                "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    for (int i = 0; i < length - 1; i++) {
        int index = rand() % (sizeof(charset) - 1);
        str[i] = charset[index];
    }
    str[length - 1] = '\\0';
}

void generate_csrf_token(const char *session_id, char *token) {
    if (token_count >= MAX_TOKENS) {
        token[0] = '\\0';
        return;
    }
    
    generate_random_string(token, TOKEN_LENGTH);
    
    strncpy(token_store[token_count].session_id, session_id, SESSION_LENGTH - 1);
    strncpy(token_store[token_count].token, token, TOKEN_LENGTH - 1);
    token_count++;
}

bool validate_csrf_token(const char *session_id, const char *token) {
    for (int i = 0; i < token_count; i++) {
        if (strcmp(token_store[i].session_id, session_id) == 0) {
            return strcmp(token_store[i].token, token) == 0;
        }
    }
    return false;
}

int main() {
    srand(time(NULL));
    
    // Test case 1: Generate and validate valid token
    char session_id1[SESSION_LENGTH] = "session1";
    char token1[TOKEN_LENGTH];
    generate_csrf_token(session_id1, token1);
    printf("Test 1: %d\\n", validate_csrf_token(session_id1, token1));
    
    // Test case 2: Invalid token
    printf("Test 2: %d\\n", validate_csrf_token(session_id1, "invalid_token"));
    
    // Test case 3: Invalid session
    printf("Test 3: %d\\n", validate_csrf_token("invalid_session", token1));
    
    // Test case 4: Multiple tokens for different sessions
    char session_id2[SESSION_LENGTH] = "session2";
    char token2[TOKEN_LENGTH];
    generate_csrf_token(session_id2, token2);
    printf("Test 4: %d\\n", validate_csrf_token(session_id2, token2));
    
    // Test case 5: Token replacement
    char new_token[TOKEN_LENGTH];
    generate_csrf_token(session_id1, new_token);
    printf("Test 5: %d\\n", validate_csrf_token(session_id1, token1));
    
    return 0;
}
