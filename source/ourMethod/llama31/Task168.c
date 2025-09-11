#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* tweakLetters(const char* word, int* tweaks, int length) {
    if (strlen(word) != length) {
        fprintf(stderr, "Word and tweaks array must be of the same length\n");
        exit(EXIT_FAILURE);
    }

    char* result = malloc((length + 1) * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < length; i++) {
        char c = word[i];
        int offset = tweaks[i];
        char newChar = (char) (c + offset);
        // Ensure the new character remains within the alphabet range
        if (newChar < 'a') {
            newChar = 'a';
        } else if (newChar > 'z') {
            newChar = 'z';
        }
        result[i] = newChar;
    }
    result[length] = '\0';
    return result;
}

int main() {
    int tweaks1[] = {0, 1, -1, 0, -1};
    int tweaks2[] = {0, 0, 0, -1};
    int tweaks3[] = {1, 1, 1, 1, 1};

    char* result1 = tweakLetters("apple", tweaks1, 5);
    char* result2 = tweakLetters("many", tweaks2, 4);
    char* result3 = tweakLetters("rhino", tweaks3, 5);

    printf("%s\n", result1); // "aqold"
    printf("%s\n", result2); // "manx"
    printf("%s\n", result3); // "sijop"

    free(result1);
    free(result2);
    free(result3);

    return 0;
}