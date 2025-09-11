#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** numberLines(char** lines, int size) {
    char** numberedLines = malloc(sizeof(char*) * size);
    if (numberedLines == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        int len = snprintf(NULL, 0, "%d: %s", i + 1, lines[i]);
        numberedLines[i] = malloc(sizeof(char) * (len + 1));
        if (numberedLines[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(numberedLines[j]);
            }
            free(numberedLines);
            return NULL;
        }
        snprintf(numberedLines[i], len + 1, "%d: %s", i + 1, lines[i]);
    }

    return numberedLines;
}

int main() {
    int size1 = 0;
    char** test1 = NULL;
    char** result1 = numberLines(test1, size1);
    // []

    int size2 = 3;
    char* test2[3] = {"a", "b", "c"};
    char** result2 = numberLines(test2, size2);
    for (int i = 0; i < size2; i++) {
        printf("%s\n", result2[i]);
        free(result2[i]);
    }
    free(result2);
    // ["1: a", "2: b", "3: c"]

    return 0;
}