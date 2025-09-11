#include <stdio.h>
#include <openssl/rand.h>

void generate_csrf_token(char *token, int token_length) {
    RAND_bytes((unsigned char *)token, token_length);
}

int main() {
    const int token_length = 24;
    char token[token_length + 1];
    generate_csrf_token(token, token_length);
    token[token_length] = '\0';

    printf("%s\n", token);

    return 0;
}