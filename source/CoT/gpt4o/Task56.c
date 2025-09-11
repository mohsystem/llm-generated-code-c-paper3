#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateToken(char *token, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t charset_size = sizeof(charset) - 1;
    
    for (size_t i = 0; i < length; i++) {
        token[i] = charset[rand() % charset_size];
    }
    token[length] = '\0';
}

int main() {
    srand(time(NULL));
    char token[25];
    
    for (int i = 0; i < 5; i++) {
        generateToken(token, 24);
        printf("%s\n", token);
    }

    return 0;
}