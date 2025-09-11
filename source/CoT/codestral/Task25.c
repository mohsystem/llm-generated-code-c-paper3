#include <stdio.h>
#include <stdlib.h>

char** lineNumbering(char** lines, int len) {
    char** numberedLines = malloc(sizeof(char*) * len);
    for (int i = 0; i < len; i++) {
        char buffer[10];
        sprintf(buffer, "%d: ", i + 1);
        int lineLen = strlen(lines[i]);
        numberedLines[i] = malloc(sizeof(char) * (strlen(buffer) + lineLen + 1));
        strcpy(numberedLines[i], buffer);
        strcat(numberedLines[i], lines[i]);
    }
    return numberedLines;
}

int main() {
    char* testCase1[] = {};
    char* testCase2[] = {"a", "b", "c"};

    char** result1 = lineNumbering(testCase1, 0);
    char** result2 = lineNumbering(testCase2, 3);

    for (int i = 0; i < 3; i++) {
        printf("%s\n", result2[i]);
        free(result2[i]);
    }
    free(result1);
    free(result2);

    return 0;
}