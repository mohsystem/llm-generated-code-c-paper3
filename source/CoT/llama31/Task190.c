#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void transposeFile(const char* fileName) {
    FILE* inputFile = fopen(fileName, "r");
    if (!inputFile) {
        fprintf(stderr, "Error opening file: %s\n", fileName);
        return;
    }

    char line[MAX_LINE_LENGTH];
    int numRows = 0;
    while (fgets(line, MAX_LINE_LENGTH, inputFile)) {
        numRows++;
    }
    rewind(inputFile);

    int numCols;
    if (fgets(line, MAX_LINE_LENGTH, inputFile)) {
        numCols = 0;
        char* token = strtok(line, " ");
        while (token) {
            numCols++;
            token = strtok(NULL, " ");
        }
    } else {
        fclose(inputFile);
        return;
    }

    char** rows = malloc(numRows * sizeof(char*));
    for (int i = 0; i < numRows; i++) {
        rows[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
        fgets(rows[i], MAX_LINE_LENGTH, inputFile);
    }
    fclose(inputFile);

    FILE* outputFile = fopen("output_" + strlen(fileName) * sizeof(char), "w");
    if (!outputFile) {
        fprintf(stderr, "Error opening output file: output_%s\n", fileName);
        return;
    }

    for (int col = 0; col < numCols; col++) {
        for (int row = 0; row < numRows; row++) {
            char* token = strtok(rows[row], " ");
            for (int i = 0; i < col; i++) {
                token = strtok(NULL, " ");
            }
            fprintf(outputFile, "%s ", token);
        }
        fprintf(outputFile, "\n");
    }

    for (int i = 0; i < numRows; i++) {
        free(rows[i]);
    }
    free(rows);
    fclose(outputFile);
}

int main() {
    const char* testFiles[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    for (int i = 0; i < 5; i++) {
        transposeFile(testFiles[i]);
    }
    return 0;
}