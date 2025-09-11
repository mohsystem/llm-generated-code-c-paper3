#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char* generateRandomString(int length) {
    if (length <= 0) {
        return "";
    }

    const char* allowedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int allowedCharsLen = strlen(allowedChars);

    char* result = (char*)malloc((length + 1) * sizeof(char));
    if (result == NULL) {
        return NULL; 
    }


    srand(time(NULL)); // Seed the random number generator once

    for (int i = 0; i < length; i++) {
        int randomIndex = rand() % allowedCharsLen;
        result[i] = allowedChars[randomIndex];
    }
    result[length] = '\0';

    return result;

}

int main() {
    char* str1 = generateRandomString(10);
    printf("%s\n", str1 ? str1 : "Memory allocation failed");
    free(str1);

    char* str2 = generateRandomString(5);
    printf("%s\n", str2 ? str2 : "Memory allocation failed");
    free(str2);


    char* str3 = generateRandomString(0);
    printf("%s\n", str3 ? str3 : "Memory allocation failed");
    free(str3);

    char* str4 = generateRandomString(20);
    printf("%s\n", str4 ? str4 : "Memory allocation failed");
    free(str4);


    char* str5 = generateRandomString(15);
    printf("%s\n", str5 ? str5 : "Memory allocation failed");
    free(str5);

    return 0;
}