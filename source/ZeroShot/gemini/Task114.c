#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* copyString(const char* str) {
    char* newStr = (char*)malloc(strlen(str) + 1);
    if (newStr == NULL) {
        return NULL; 
    }
    strcpy(newStr, str);
    return newStr;
}

char* concatenateStrings(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) return NULL;
    char* newStr = (char*)malloc(strlen(str1) + strlen(str2) + 1);
    if (newStr == NULL) {
        return NULL;
    }
    strcpy(newStr, str1);
    strcat(newStr, str2);
    return newStr;
}

char* reverseString(const char* str) {
    char *reversedStr = (char*) malloc(strlen(str) + 1);
    if (reversedStr == NULL) return NULL;
    int len = strlen(str);
    for(int i = 0; i < len; i++) {
        reversedStr[i] = str[len - 1 - i];
    }
    reversedStr[len] = '\0';
    return reversedStr;

}


char* toUpperCase(const char* str) {
    char *upperStr = (char*)malloc(strlen(str) + 1);
    if (upperStr == NULL) return NULL;

    strcpy(upperStr, str);
    for (int i = 0; upperStr[i] != '\0'; i++) {
        upperStr[i] = toupper(upperStr[i]);
    }
    return upperStr;

}

int main() {
    char* copied = copyString("hello");
    char* concatenated = concatenateStrings("hello", " world");
    char *reversed = reverseString("hello");
    char *upper = toUpperCase("hello");

     char *str1 = NULL;
    char *concatenated_null = concatenateStrings(str1, " world");

    if (copied != NULL) printf("Copy: %s\n", copied);
    if (concatenated != NULL) printf("Concatenate: %s\n", concatenated);
    if (reversed != NULL) printf("Reverse: %s\n", reversed);
    if (upper != NULL) printf("Upper Case: %s\n", upper);
    if (concatenated_null == NULL) printf("Concatenate null with string: (null)\n");

    free(copied);
    free(concatenated);
    free(reversed);
    free(upper);
    free(concatenated_null);


    return 0;
}