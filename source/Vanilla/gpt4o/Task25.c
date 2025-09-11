#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** numberLines(char* lines[], int count) {
    char** numberedLines = malloc(count * sizeof(char*));
    for (int i = 0; i < count; ++i) {
        int len = snprintf(NULL, 0, "%d: %s", i + 1, lines[i]);
        numberedLines[i] = malloc(len + 1);
        snprintf(numberedLines[i], len + 1, "%d: %s", i + 1, lines[i]);
    }
    return numberedLines;
}

void freeNumberedLines(char** numberedLines, int count) {
    for (int i = 0; i < count; ++i) {
        free(numberedLines[i]);
    }
    free(numberedLines);
}

int main() {
    char* test1[] = {};
    char* test2[] = {"a", "b", "c"};
    char* test3[] = {"first", "second", "third"};
    char* test4[] = {"line1"};
    char* test5[] = {"Hello", "World!"};

    char** result1 = numberLines(test1, 0);
    char** result2 = numberLines(test2, 3);
    char** result3 = numberLines(test3, 3);
    char** result4 = numberLines(test4, 1);
    char** result5 = numberLines(test5, 2);

    for (int i = 0; i < 0; ++i) {
        printf("%s\n", result1[i]);
    }
    freeNumberedLines(result1, 0);

    for (int i = 0; i < 3; ++i) {
        printf("%s\n", result2[i]);
    }
    freeNumberedLines(result2, 3);

    for (int i = 0; i < 3; ++i) {
        printf("%s\n", result3[i]);
    }
    freeNumberedLines(result3, 3);

    for (int i = 0; i < 1; ++i) {
        printf("%s\n", result4[i]);
    }
    freeNumberedLines(result4, 1);

    for (int i = 0; i < 2; ++i) {
        printf("%s\n", result5[i]);
    }
    freeNumberedLines(result5, 2);

    return 0;
}