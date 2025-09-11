#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void transposeFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    char *lines[100]; // Assuming no more than 100 lines
    int lineCount = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, file)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
        lines[lineCount] = strdup(buffer);
        lineCount++;
    }
    fclose(file);

    char *tokens[100][100]; // Assuming no more than 100 tokens per line
    int columnCount = 0;
    for (int i = 0; i < lineCount; i++) {
        char *token = strtok(lines[i], " ");
        int tokenCount = 0;
        while (token) {
            tokens[i][tokenCount++] = token;
            token = strtok(NULL, " ");
        }
        columnCount = tokenCount;
    }

    for (int i = 0; i < columnCount; i++) {
        for (int j = 0; j < lineCount; j++) {
            if (j > 0) printf(" ");
            printf("%s", tokens[j][i]);
        }
        printf("\n");
    }

    for (int i = 0; i < lineCount; i++) {
        free(lines[i]);
    }
}

int main() {
    const char *testFile = "file.txt";
    transposeFile(testFile);
    return 0;
}