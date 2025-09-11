#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* generateRandomString(int length) {
    if (length <= 0) {
        fprintf(stderr, "Length should be a positive integer\n");
        exit(EXIT_FAILURE);
    }

    const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int characters_length = sizeof(characters) - 1;

    char* result = malloc(length + 1);
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    for (int i = 0; i < length; ++i) {
        result[i] = characters[rand() % characters_length];
    }

    result[length] = '\0';
    return result;
}

int main() {
    char* str1 = generateRandomString(10);
    printf("%s\n", str1);
    free(str1);

    char* str2 = generateRandomString(15);
    printf("%s\n", str2);
    free(str2);

    char* str3 = generateRandomString(5);
    printf("%s\n", str3);
    free(str3);

    char* str4 = generateRandomString(20);
    printf("%s\n", str4);
    free(str4);

    char* str5 = generateRandomString(8);
    printf("%s\n", str5);
    free(str5);

    return 0;
}