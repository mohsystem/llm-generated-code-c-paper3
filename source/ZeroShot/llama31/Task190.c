#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transposeFile(const char* inputFile) {
    FILE* reader = fopen(inputFile, "r");
    FILE* writer = fopen("output_" + strlen(inputFile), "w");
    if (!reader || !writer) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    char line[1024];
    int rows = 0, cols = 0;
    while (fgets(line, sizeof(line), reader)) {
        if (rows == 0) {
            cols = 0;
            char* token = strtok(line, " ");
            while (token) {
                cols++;
                token = strtok(NULL, " ");
            }
        }
        rows++;
    }

    rewind(reader);
    char** data = malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        data[i] = malloc(cols * sizeof(char*));
        for (int j = 0; j < cols; j++) {
            data[i][j] = malloc(1024 * sizeof(char));
        }
    }

    int row = 0;
    while (fgets(line, sizeof(line), reader)) {
        char* token = strtok(line, " ");
        for (int col = 0; col < cols; col++) {
            strcpy(data[row][col], token);
            token = strtok(NULL, " ");
        }
        row++;
    }

    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            fprintf(writer, "%s ", data[row][col]);
        }
        fprintf(writer, "\n");
    }

    fclose(reader);
    fclose(writer);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);
}

int main() {
    const char* testFiles[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"};
    for (int i = 0; i < 5; i++) {
        transposeFile(testFiles[i]);
    }
    return 0;
}