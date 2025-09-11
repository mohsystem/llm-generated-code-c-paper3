#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_TOKENS 100

void transposeFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    char** lines[MAX_TOKENS];
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;
    int tokenCount = 0;

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char* token = strtok(line, " ");
        int tokenIndex = 0;

        while (token != NULL) {
            if (lineCount == 0) {
                lines[tokenIndex] = (char**)malloc(sizeof(char*) * MAX_TOKENS);
            }

            lines[tokenIndex][lineCount] = strdup(token);

            token = strtok(NULL, " ");
            tokenIndex++;
        }

        if (lineCount == 0) {
            tokenCount = tokenIndex;
        }

        lineCount++;
    }

    for (int i = 0; i < tokenCount; i++) {
        for (int j = 0; j < lineCount; j++) {
            printf("%s ", lines[i][j]);
        }
        printf("\n");
    }

    fclose(file);
}

int main() {
    transposeFile("file.txt");
    return 0;
}