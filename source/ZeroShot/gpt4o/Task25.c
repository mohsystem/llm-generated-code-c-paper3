#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** numberLines(char* lines[], int count, int* resultSize) {
    char** numberedLines = (char**)malloc(count * sizeof(char*));
    for (int i = 0; i < count; i++) {
        int len = snprintf(NULL, 0, "%d: %s", i + 1, lines[i]) + 1;
        numberedLines[i] = (char*)malloc(len * sizeof(char));
        snprintf(numberedLines[i], len, "%d: %s", i + 1, lines[i]);
    }
    *resultSize = count;
    return numberedLines;
}

int main() {
    int resultSize;
    char* lines1[] = {};
    char* lines2[] = {"a", "b", "c"};
    char* lines3[] = {"Hello", "World"};
    char* lines4[] = {"Java", "Python", "C++"};
    char* lines5[] = {"One line"};

    char** result1 = numberLines(lines1, 0, &resultSize);
    char** result2 = numberLines(lines2, 3, &resultSize);
    char** result3 = numberLines(lines3, 2, &resultSize);
    char** result4 = numberLines(lines4, 3, &resultSize);
    char** result5 = numberLines(lines5, 1, &resultSize);

    // Print test results
    for (int i = 0; i < resultSize; i++) {
        printf("%s\n", result1[i]);
    }
    for (int i = 0; i < resultSize; i++) {
        printf("%s\n", result2[i]);
    }
    for (int i = 0; i < resultSize; i++) {
        printf("%s\n", result3[i]);
    }
    for (int i = 0; i < resultSize; i++) {
        printf("%s\n", result4[i]);
    }
    for (int i = 0; i < resultSize; i++) {
        printf("%s\n", result5[i]);
    }

    return 0;
}