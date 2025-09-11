#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void transposeFile(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        fprintf(stderr, "File not found: %s\n", fileName);
        return;
    }

    char line[1024];
    int rows = 0;
    int cols = 0;

    // Determine the number of rows and columns
    while (fgets(line, sizeof(line), file)) {
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
    rewind(file);

    // Allocate memory for the matrix
    char*** matrix = malloc(rows * sizeof(char**));
    for (int i = 0; i < rows; i++) {
        matrix[i] = malloc(cols * sizeof(char*));
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = malloc(1024 * sizeof(char));
        }
    }

    // Read the file into the matrix
    int row = 0;
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, " ");
        int col = 0;
        while (token) {
            strcpy(matrix[row][col], token);
            token = strtok(NULL, " ");
            col++;
        }
        row++;
    }
    fclose(file);

    // Transpose the matrix
    char*** transposedMatrix = malloc(cols * sizeof(char**));
    for (int i = 0; i < cols; i++) {
        transposedMatrix[i] = malloc(rows * sizeof(char*));
        for (int j = 0; j < rows; j++) {
            transposedMatrix[i][j] = malloc(1024 * sizeof(char));
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            strcpy(transposedMatrix[j][i], matrix[i][j]);
        }
    }

    // Print the transposed matrix
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            printf("%s ", transposedMatrix[i][j]);
        }
        printf("\n");
    }

    // Free the memory
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);

    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            free(transposedMatrix[i][j]);
        }
        free(transposedMatrix[i]);
    }
    free(transposedMatrix);
}

int main() {
    transposeFile("file.txt");
    return 0;
}