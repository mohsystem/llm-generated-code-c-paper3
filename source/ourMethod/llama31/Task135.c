#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <base64.h> // You may need to include a base64 library

typedef struct {
    char* token;
    struct csrf_token* next;
} csrf_token;

csrf_token* csrf_tokens = NULL;

char* generate_csrf_token() {
    static char token[33];
    for (int i = 0; i < 32; ++i) {
        token[i] = (char)(rand() % 256);
    }
    token[32] = '\0';

    // Base64 encode the token
    char* encodedToken = base64_encode(token, 32);
    csrf_token* newToken = malloc(sizeof(csrf_token));
    newToken->token = encodedToken;
    newToken->next = csrf_tokens;
    csrf_tokens = newToken;
    return encodedToken;
}

int validate_csrf_token(const char* token) {
    csrf_token* current = csrf_tokens;
    while (current != NULL) {
        if (strcmp(current->token, token) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int main() {
    srand(time(NULL));

    // Generate and validate tokens
    char* token = generate_csrf_token();
    printf("Generated Token: %s\n", token);
    printf("Token Valid: %d\n", validate_csrf_token(token));

    // Test cases
    printf("Token Valid (invalid token): %d\n", validate_csrf_token("invalid-token"));
    printf("Token Valid (null token): %d\n", validate_csrf_token(NULL));

    // Generate and validate multiple tokens
    char* token2 = generate_csrf_token();
    printf("Generated Token 2: %s\n", token2);
    printf("Token 2 Valid: %d\n", validate_csrf_token(token2));
    printf("Token 1 Valid after generating token 2: %d\n", validate_csrf_token(token));

    return 0;
}