#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void generateRandomString(int length, char* str) {
    // Define ASCII letters
    const char* allLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    // Initialize random number generator
    srand(time(NULL));

    // Generate random string
    for (int i = 0; i < length; ++i) {
        int index = rand() % strlen(allLetters);
        str[i] = allLetters[index];
    }
    str[length] = '\0'; // Null terminate the string
}

int main() {
    char str[26]; // Maximum length + 1 for null terminator

    // Test cases
    generateRandomString(5, str);
    printf("%s\n", str);

    generateRandomString(10, str);
    printf("%s\n", str);

    generateRandomString(15, str);
    printf("%s\n", str);

    generateRandomString(20, str);
    printf("%s\n", str);

    generateRandomString(25, str);
    printf("%s\n", str);

    return 0;
}