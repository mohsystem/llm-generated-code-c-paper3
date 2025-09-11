#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* generateRandomString(int length) {
    char* randomString = (char*) malloc((length + 1) * sizeof(char));
    char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        int index = rand() % 52;
        randomString[i] = alphabet[index];
    }
    randomString[length] = '\0';
    return randomString;
}

int main() {
    for (int i = 0; i < 5; i++) {
        char* str = generateRandomString(10);
        printf("%s\n", str);
        free(str);
    }
    return 0;
}