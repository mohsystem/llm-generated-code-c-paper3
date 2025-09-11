#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_token(char* token, size_t length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const int charset_length = sizeof(charset) - 1;

    for (size_t i = 0; i < length; i++) {
        token[i] = charset[rand() % charset_length];
    }
    token[length] = '\0';
}

int main() {
    srand(time(NULL));
    char token[25];
    generate_token(token, 24);
    printf("%s\n", token);
    return 0;
}