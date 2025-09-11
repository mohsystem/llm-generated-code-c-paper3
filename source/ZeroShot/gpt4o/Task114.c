#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* copyString(const char* input) {
    if (input == NULL) return NULL;
    char* copy = malloc(strlen(input) + 1);
    if (copy == NULL) return NULL;
    strcpy(copy, input);
    return copy;
}

char* concatenateStrings(const char* str1, const char* str2) {
    if (str1 == NULL) str1 = "";
    if (str2 == NULL) str2 = "";
    char* result = malloc(strlen(str1) + strlen(str2) + 1);
    if (result == NULL) return NULL;
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

char* reverseString(const char* input) {
    if (input == NULL) return NULL;
    size_t len = strlen(input);
    char* reversed = malloc(len + 1);
    if (reversed == NULL) return NULL;
    for (size_t i = 0; i < len; i++) {
        reversed[i] = input[len - 1 - i];
    }
    reversed[len] = '\0';
    return reversed;
}

int main() {
    char* result;

    result = copyString("hello");
    printf("%s\n", result); // hello
    free(result);

    result = concatenateStrings("hello", "world");
    printf("%s\n", result); // helloworld
    free(result);

    result = reverseString("hello");
    printf("%s\n", result); // olleh
    free(result);

    return 0;
}