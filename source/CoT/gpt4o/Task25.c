#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** numberLines(char* lines[], int size) {
    char** numberedLines = malloc(size * sizeof(char*));
    for (int i = 0; i < size; ++i) {
        int len = snprintf(NULL, 0, "%d: %s", i + 1, lines[i]);
        numberedLines[i] = malloc(len + 1);
        snprintf(numberedLines[i], len + 1, "%d: %s", i + 1, lines[i]);
    }
    return numberedLines;
}

void printLines(char* lines[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%s\n", lines[i]);
    }
}

int main() {
    char* test1[] = {};
    char* test2[] = {"a", "b", "c"};
    char* test3[] = {"Hello", "World"};
    char* test4[] = {"C", "is", "fun"};
    char* test5[] = {"Test", "case", "five"};

    char** result1 = numberLines(test1, 0);
    char** result2 = numberLines(test2, 3);
    char** result3 = numberLines(test3, 2);
    char** result4 = numberLines(test4, 3);
    char** result5 = numberLines(test5, 3);

    printLines(result1, 0);
    printLines(result2, 3);
    printLines(result3, 2);
    printLines(result4, 3);
    printLines(result5, 3);

    for (int i = 0; i < 3; ++i) {
        free(result2[i]);
        free(result4[i]);
        free(result5[i]);
    }
    for (int i = 0; i < 2; ++i) {
        free(result3[i]);
    }
    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);

    return 0;
}