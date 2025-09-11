#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char* generateRandomString(int length) {
    const char* allAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int alphabetSize = strlen(allAlphabet);
    char* randomString = (char*) malloc((length + 1) * sizeof(char));
    randomString[length] = '\0'; // Null terminate the string

    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        int index = rand() % alphabetSize;
        randomString[i] = allAlphabet[index];
    }

    return randomString;
}

int main() {
    // Test cases
    char* str;
    str = generateRandomString(5);
    printf("%s\n", str);
    free(str);

    str = generateRandomString(10);
    printf("%s\n", str);
    free(str);

    str = generateRandomString(7);
    printf("%s\n", str);
    free(str);

    str = generateRandomString(3);
    printf("%s\n", str);
    free(str);

    str = generateRandomString(15);
    printf("%s\n", str);
    free(str);

    return 0;
}