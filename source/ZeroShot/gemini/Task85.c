#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomString(int length) {
    char *randomString = (char *)malloc((length + 1) * sizeof(char));
    const char allowedChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int allowedCharsLen = strlen(allowedChars);

    srand((unsigned int)time(NULL)); // Seed the random number generator

    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % allowedCharsLen;
        randomString[i] = allowedChars[randomIndex];
    }
    randomString[length] = '\0';

    return randomString;
}

int main() {
    char *str1 = generateRandomString(10);
    printf("%s\n", str1);
    free(str1);

    char *str2 = generateRandomString(5);
    printf("%s\n", str2);
    free(str2);
    
    char *str3 = generateRandomString(20);
    printf("%s\n", str3);
    free(str3);

    char *str4 = generateRandomString(15);
    printf("%s\n", str4);
    free(str4);

    char *str5 = generateRandomString(8);
    printf("%s\n", str5);
    free(str5);

    return 0;
}