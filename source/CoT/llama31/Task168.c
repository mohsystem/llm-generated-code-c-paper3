#include <stdio.h>
#include <string.h>

void main() {
    char result[100];
    tweakLetters("apple", (int[]) {0, 1, -1, 0, -1}, result); printf("%s\n", result); // "aqold"
    tweakLetters("many", (int[]) {0, 0, 0, -1}, result); printf("%s\n", result); // "manx"
    tweakLetters("rhino", (int[]) {1, 1, 1, 1, 1}, result); printf("%s\n", result); // "sijop"
    tweakLetters("test", (int[]) {0, 0, 0, 0}, result); printf("%s\n", result); // "test"
    tweakLetters("hello", (int[]) {-1, -1, -1, -1, -1}, result); printf("%s\n", result); // "gdkkk"
}

void tweakLetters(const char* str, int arr[], char* result) {
    strcpy(result, str);
    for (int i = 0; i < strlen(str); i++) {
        result[i] = (char) (result[i] + arr[i]);
    }
}