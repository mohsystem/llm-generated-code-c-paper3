#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateToken(char* buffer, size_t length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t charsetSize = sizeof(charset) - 1;
    
    srand(time(NULL));
    for (size_t i = 0; i < length; ++i) {
        buffer[i] = charset[rand() % charsetSize];
    }
    buffer[length] = '\0';
}

int main() {
    char token[33];
    for (int i = 0; i < 5; ++i) {
        generateToken(token, 32);
        printf("Generated Token: %s\n", token);
    }
    return 0;
}