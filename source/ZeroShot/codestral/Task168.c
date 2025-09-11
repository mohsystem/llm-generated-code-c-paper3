#include <stdio.h>
#include <string.h>

void tweakLetters(char* str, int arr[], char* result) {
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        result[i] = str[i] + arr[i];
    }

    result[len] = '\0';
}

int main() {
    char result[100];
    tweakLetters("apple", (int[]){0, 1, -1, 0, -1}, result);
    printf("%s\n", result); // ➞ "aqold"
    tweakLetters("many", (int[]){0, 0, 0, -1}, result);
    printf("%s\n", result); // ➞ "manx"
    tweakLetters("rhino", (int[]){1, 1, 1, 1, 1}, result);
    printf("%s\n", result); // ➞ "sijop"
    return 0;
}