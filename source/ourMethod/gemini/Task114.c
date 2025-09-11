#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* copyString(const char* str) {
    char* copy = (char*)malloc(strlen(str) + 1);
    if (copy == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    strcpy(copy, str);
    return copy;
}

char* concatenateStrings(const char* str1, const char* str2) {
    char* concatenated = (char*)malloc(strlen(str1) + strlen(str2) + 1);
    if (concatenated == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    strcpy(concatenated, str1);
    strcat(concatenated, str2);
    return concatenated;
}

char* reverseString(const char* str) {
    size_t len = strlen(str);
    char* reversed = (char*)malloc(len + 1);
    if (reversed == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
    return reversed;
}


char* toUpperCase(const char* str) {
    size_t len = strlen(str);
    char* upper = (char*)malloc(len + 1);
    if (upper == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < len; i++) {
        upper[i] = toupper(str[i]);
    }
    upper[len] = '\0';
    return upper;
}

char* toLowerCase(const char* str) {
    size_t len = strlen(str);
    char* lower = (char*)malloc(len + 1);
    if (lower == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < len; i++) {
        lower[i] = tolower(str[i]);
    }
    lower[len] = '\0';
    return lower;
}


int main() {
    char test1[] = "Hello";
    char* copy = copyString(test1);
    printf("Copy: %s\n", copy);
    free(copy);

    char test2_1[] = "Hello";
    char test2_2[] = "World";
    char* concatenated = concatenateStrings(test2_1, test2_2);
    printf("Concatenated: %s\n", concatenated);
    free(concatenated);

    char test3[] = "Reverse";
    char* reversed = reverseString(test3);
    printf("Reversed: %s\n", reversed);
    free(reversed);
    
    char test4[] = "uppercase";
    char* upper = toUpperCase(test4);
    printf("Uppercase: %s\n", upper);
    free(upper);

    char test5[] = "LOWERCASE";
    char* lower = toLowerCase(test5);
    printf("Lowercase: %s\n", lower);
    free(lower);

    return 0;
}