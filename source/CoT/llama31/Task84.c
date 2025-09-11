#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomString(char* str, int length) {
    const char characters[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length; i++) {
        str[i] = characters[rand() % sizeof(characters) - 1];
    }
    str[length] = '\0';
}

int main() {
    srand(time(NULL));
    char sessionID[33];

    for (int i = 0; i < 5; i++) {
        generateRandomString(sessionID, 32);
        printf("Session ID: %s\n", sessionID);
    }

    return 0;
}