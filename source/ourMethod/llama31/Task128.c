#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TOKEN_LENGTH 10

void generateRandomToken(char* token) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < TOKEN_LENGTH; ++i) {
        token[i] = characters[rand() % (sizeof(characters) - 1)];
    }
    token[TOKEN_LENGTH] = '\0';
}

int generateRandomNumber() {
    return rand() % 1000;
}

int main() {
    srand(time(NULL)); // Initialize random number generator

    for (int i = 0; i < 5; ++i) {
        printf("Random Number: %d\n", generateRandomNumber());
        char token[TOKEN_LENGTH + 1];
        generateRandomToken(token);
        printf("Random Token: %s\n", token);
    }
    return 0;
}