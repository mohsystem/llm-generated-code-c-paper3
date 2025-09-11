#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomToken(int length) {
    char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    char* token = (char*)malloc(sizeof(char) * (length + 1));
    if (token == NULL) {
        return NULL; 
    }

    srand(time(NULL)); 
    for (int i = 0; i < length; i++) {
        token[i] = characters[rand() % (sizeof(characters) - 1)];
    }
    token[length] = '\0';
    return token;
}

int main() {
    char* token1 = generateRandomToken(10);
    printf("%s\n", token1);
    free(token1);

    char* token2 = generateRandomToken(5);
    printf("%s\n", token2);
    free(token2);

    char* token3 = generateRandomToken(15);
    printf("%s\n", token3);
    free(token3);


    char* token4 = generateRandomToken(8);
    printf("%s\n", token4);
    free(token4);

    char* token5 = generateRandomToken(12);
    printf("%s\n", token5);
    free(token5);

    return 0;
}