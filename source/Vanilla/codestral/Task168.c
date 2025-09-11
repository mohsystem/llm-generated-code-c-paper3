#include <stdio.h>
#include <string.h>

void tweakLetters(char *word, int *tweaks, char *result) {
    for (int i = 0; i < strlen(word); i++) {
        result[i] = word[i] + tweaks[i];
    }
    result[strlen(word)] = '\0';
}

int main() {
    char result[100];
    int tweaks1[] = {0, 1, -1, 0, -1};
    tweakLetters("apple", tweaks1, result);
    printf("%s\n", result);
    int tweaks2[] = {0, 0, 0, -1};
    tweakLetters("many", tweaks2, result);
    printf("%s\n", result);
    int tweaks3[] = {1, 1, 1, 1, 1};
    tweakLetters("rhino", tweaks3, result);
    printf("%s\n", result);
    return 0;
}