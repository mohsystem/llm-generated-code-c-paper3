#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Simplified CSRF token generation (not cryptographically secure)
char* generate_csrf_token() {
    char* token = (char*)malloc(33 * sizeof(char)); // 32 characters + null terminator
    if (token == NULL) {
        return NULL;
    }

    srand(time(NULL)); 
    for (int i = 0; i < 32; i++) {
        token[i] = "0123456789abcdef"[rand() % 16];
    }
    token[32] = '\0';
    return token;
}

bool validate_csrf_token(const char* request_token, const char* stored_token) {
    return strcmp(request_token, stored_token) == 0;
}

int main() {
    // Test cases
    char* token1 = generate_csrf_token();
    printf("Token 1: %s\n", token1);
    printf("Valid Token 1: %s\n", validate_csrf_token(token1, token1) ? "true" : "false");
    printf("Invalid Token 1: %s\n", validate_csrf_token("wrong_token", token1) ? "true" : "false");
    free(token1);



    char* token2 = generate_csrf_token();
    printf("Token 2: %s\n", token2);
    printf("Valid Token 2: %s\n", validate_csrf_token(token2, token2) ? "true" : "false");
    free(token2);

    char* token3 = generate_csrf_token();
    printf("Token 3: %s\n", token3);
    printf("Valid Token 3: %s\n", validate_csrf_token(token3, token3) ? "true" : "false");
    free(token3);

    char* token4 = generate_csrf_token();
    printf("Token 4: %s\n", token4);
    printf("Valid Token 4: %s\n", validate_csrf_token(token4, token4) ? "true" : "false");
    free(token4);


    char* token5 = generate_csrf_token();
    printf("Token 5: %s\n", token5);
    printf("Valid Token 5: %s\n", validate_csrf_token(token5, token5) ? "true" : "false");
    free(token5);



    return 0;
}