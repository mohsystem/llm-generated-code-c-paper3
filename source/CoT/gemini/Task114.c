#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* copyString(const char* str) {
    size_t len = strlen(str);
    char* copiedString = (char*)malloc((len + 1) * sizeof(char));
    if (copiedString == NULL) {
        return NULL; // Handle memory allocation failure
    }
    strcpy(copiedString, str);
    return copiedString;
}

char* concatenateStrings(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char* concatenatedString = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    if (concatenatedString == NULL) {
        return NULL; // Handle memory allocation failure
    }
    strcpy(concatenatedString, str1);
    strcat(concatenatedString, str2);
    return concatenatedString;
}

char* reverseString(const char *str) {
    size_t len = strlen(str);
    char *reversedString = (char*)malloc((len + 1) * sizeof(char));
    if (reversedString == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        reversedString[i] = str[len - 1 - i];
    }
    reversedString[len] = '\0';
    return reversedString;
}


int main() {
    char* copied = copyString("Hello");
    char* concatenated = concatenateStrings("Hello", " World");
    char *reversed = reverseString("Hello");

    printf("Copy String: %s\n", copied);
    printf("Concatenate Strings: %s\n", concatenated);
    printf("Reverse String: %s\n", reversed);

    free(copied);
    free(concatenated);
    free(reversed);


    copied = copyString("OpenAI");
    concatenated = concatenateStrings("C", " Programming");


    printf("Copy String: %s\n", copied);
    printf("Concatenate Strings: %s\n", concatenated);

    free(copied);
    free(concatenated);

    return 0;
}