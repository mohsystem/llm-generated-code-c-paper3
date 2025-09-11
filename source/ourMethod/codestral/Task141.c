#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* reverseString(const char* input) {
    if (input == NULL) {
        fprintf(stderr, "Input string cannot be NULL\n");
        exit(EXIT_FAILURE);
    }

    size_t len = strlen(input);
    char* reversed = (char*)malloc((len + 1) * sizeof(char));
    if (reversed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < len; i++) {
        reversed[i] = input[len - 1 - i];
    }
    reversed[len] = '\0';

    return reversed;
}

int main() {
    char* result = reverseString("Hello, World!");
    printf("%s\n", result);
    free(result);

    result = reverseString("1234567890");
    printf("%s\n", result);
    free(result);

    result = reverseString("");
    printf("%s\n", result);
    free(result);

    result = reverseString("a");
    printf("%s\n", result);
    free(result);

    result = reverseString("ab");
    printf("%s\n", result);
    free(result);

    return 0;
}