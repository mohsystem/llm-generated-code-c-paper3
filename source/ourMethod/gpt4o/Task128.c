#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomNumber(int min, int max, int* result) {
    *result = rand() % (max - min + 1) + min;
}

void generateRandomToken(int length, char* token) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    for (int i = 0; i < length; i++) {
        token[i] = characters[rand() % (sizeof(characters) - 1)];
    }
    token[length] = '\0';
}

int main() {
    srand((unsigned int)time(NULL));

    int randomNumber;
    char randomToken[16];

    // Test cases
    generateRandomNumber(1, 100, &randomNumber);
    printf("%d\n", randomNumber); // Random number between 1 and 100

    generateRandomToken(10, randomToken);
    printf("%s\n", randomToken); // Random token of length 10

    generateRandomNumber(1, 50, &randomNumber);
    printf("%d\n", randomNumber); // Random number between 1 and 50

    generateRandomToken(15, randomToken);
    printf("%s\n", randomToken); // Random token of length 15

    generateRandomNumber(10, 20, &randomNumber);
    printf("%d\n", randomNumber); // Random number between 10 and 20

    return 0;
}