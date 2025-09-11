#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generateRandomToken(char* token, int length) {
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < length; i++) {
        token[i] = chars[rand() % (sizeof(chars) - 1)];
    }
    token[length] = '\0';
}

int generateRandomNumber(int max) {
    return rand() % (max + 1);
}

int main() {
    srand(time(NULL));
    for (int i = 0; i < 5; i++) {
        printf("%d\n", generateRandomNumber(100));
        char token[11];
        generateRandomToken(token, 10);
        printf("%s\n", token);
    }
    return 0;
}