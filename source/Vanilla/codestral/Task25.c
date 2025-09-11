#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** number(char** lines, int size, int* newSize) {
    char** numberedLines = malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        char buf[10];
        sprintf(buf, "%d: ", i + 1);
        numberedLines[i] = malloc(strlen(buf) + strlen(lines[i]) + 1);
        strcpy(numberedLines[i], buf);
        strcat(numberedLines[i], lines[i]);
    }
    *newSize = size;
    return numberedLines;
}

int main() {
    int size1 = 0;
    int newSize1;
    char** result1 = number(NULL, size1, &newSize1);
    for (int i = 0; i < newSize1; i++) {
        printf("%s\n", result1[i]);
        free(result1[i]);
    }
    free(result1); // []

    char* test2[] = {"a", "b", "c"};
    int size2 = 3;
    int newSize2;
    char** result2 = number(test2, size2, &newSize2);
    for (int i = 0; i < newSize2; i++) {
        printf("%s\n", result2[i]);
        free(result2[i]);
    }
    free(result2); // 1: a, 2: b, 3: c

    return 0;
}