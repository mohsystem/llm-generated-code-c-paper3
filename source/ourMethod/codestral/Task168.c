#include <stdio.h>
#include <string.h>

void tweakLetters(char* word, int* tweaks, int len, char* result) {
    for (int i = 0; i < len; i++) {
        result[i] = word[i] + tweaks[i];
    }
    result[len] = '\0';
}

int main() {
    char result[10];
    int tweaks1[] = {0, 1, -1, 0, -1};
    tweakLetters("apple", tweaks1, 5, result);
    printf("%s\n", result); // "aqold"
    int tweaks2[] = {0, 0, 0, -1};
    tweakLetters("many", tweaks2, 4, result);
    printf("%s\n", result); // "manx"
    int tweaks3[] = {1, 1, 1, 1, 1};
    tweakLetters("rhino", tweaks3, 5, result);
    printf("%s\n", result); // "sijop"
    return 0;
}