#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void copyString(const char* input, char** output) {
    *output = (char*)malloc(strlen(input) + 1);
    if (*output == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(*output, input);
}

void concatenateStrings(const char* str1, const char* str2, char** output) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    *output = (char*)malloc(len1 + len2 + 1);
    if (*output == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(*output, str1);
    strcat(*output, str2);
}

void toUpperCase(const char* input, char** output) {
    *output = (char*)malloc(strlen(input) + 1);
    if (*output == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strcpy(*output, input);
    for (size_t i = 0; (*output)[i]; ++i) {
        (*output)[i] = toupper((*output)[i]);
    }
}

void getSubstring(const char* input, size_t start, size_t end, char** output) {
    if (start >= strlen(input) || end > strlen(input) || start > end) {
        printf("Invalid indices\n");
        exit(EXIT_FAILURE);
    }
    size_t len = end - start;
    *output = (char*)malloc(len + 1);
    if (*output == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    strncpy(*output, input + start, len);
    (*output)[len] = '\0';
}

int main() {
    // Test cases
    const char* str1 = "Hello";
    const char* str2 = " World!";
    const char* str3 = "This is a test string";

    char* copiedStr;
    copyString(str1, &copiedStr);
    printf("Copied String: %s\n", copiedStr);
    free(copiedStr);

    char* concatenatedStr;
    concatenateStrings(str1, str2, &concatenatedStr);
    printf("Concatenated String: %s\n", concatenatedStr);
    free(concatenatedStr);

    char* upperCaseStr;
    toUpperCase(str3, &upperCaseStr);
    printf("Upper Case String: %s\n", upperCaseStr);
    free(upperCaseStr);

    char* subStr;
    getSubstring(str3, 5, 10, &subStr);
    printf("Substring: %s\n", subStr);
    free(subStr);

    return 0;
}