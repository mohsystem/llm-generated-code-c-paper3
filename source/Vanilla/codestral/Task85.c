#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *generateRandomString(int length) {
    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int charactersLength = sizeof(characters) - 1;

    char *result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        result[i] = characters[rand() % charactersLength];
    }

    result[length] = '\0';
    return result;
}

int main() {
    printf("%s\n", generateRandomString(5));
    printf("%s\n", generateRandomString(10));
    printf("%s\n", generateRandomString(15));
    printf("%s\n", generateRandomString(20));
    printf("%s\n", generateRandomString(25));

    return 0;
}