#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* tweakLetters(const char* str, const int* tweaks, size_t len) {
    if (str == NULL || tweaks == NULL || len == 0) {
        fprintf(stderr, "Invalid input\n");
        exit(1);
    }
    char* result = (char*)malloc((len + 1) * sizeof(char));
    if (!result) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    for (size_t i = 0; i < len; ++i) {
        result[i] = str[i] + tweaks[i];
    }
    result[len] = '\0';
    return result;
}

int main() {
    int tweaks1[] = {0, 1, -1, 0, -1};
    int tweaks2[] = {0, 0, 0, -1};
    int tweaks3[] = {1, 1, 1, 1, 1};
    int tweaks4[] = {-1, 0, 1, 1};
    int tweaks5[] = {1, -1, 1, -1};

    char* result1 = tweakLetters("apple", tweaks1, 5);
    char* result2 = tweakLetters("many", tweaks2, 4);
    char* result3 = tweakLetters("rhino", tweaks3, 5);
    char* result4 = tweakLetters("code", tweaks4, 4);
    char* result5 = tweakLetters("java", tweaks5, 4);

    printf("%s\n", result1); // "aqold"
    printf("%s\n", result2); // "manx"
    printf("%s\n", result3); // "sijop"
    printf("%s\n", result4); // "bnff"
    printf("%s\n", result5); // "kbwb"

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);

    return 0;
}