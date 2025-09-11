#include <stdio.h>
#include <string.h>

void tweakLetters(char *word, int *tweaks, int size, char *result) {
    for (int i = 0; i < size; i++) {
        result[i] = word[i] + tweaks[i];
    }
    result[size] = '\0';
}

int main() {
    char result[6]; // accommodate the largest test case
    tweakLetters("apple", (int[]){0, 1, -1, 0, -1}, 5, result);
    printf("%s\n", result); // "aqold"
    tweakLetters("many", (int[]){0, 0, 0, -1}, 4, result);
    printf("%s\n", result); // "manx"
    tweakLetters("rhino", (int[]){1, 1, 1, 1, 1}, 5, result);
    printf("%s\n", result); // "sijop"
    tweakLetters("code", (int[]){1, 0, -1, 2}, 4, result);
    printf("%s\n", result); // "dodb"
    tweakLetters("java", (int[]){0, 0, 0, 0}, 4, result);
    printf("%s\n", result); // "java"
    return 0;
}