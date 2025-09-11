
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_LENGTH 1000

char* transpose_file(char** input, int num_rows) {
    if (input == NULL || num_rows == 0) {
        return NULL;
    }

    // Count columns in first row
    int num_cols = 1;
    for (char* p = input[0]; *p; p++) {
        if (*p == ' ') num_cols++;
    }

    // Create matrix to store words
    char matrix[MAX_ROWS][MAX_COLS][MAX_LENGTH];
    int row = 0;

    for (int i = 0; i < num_rows; i++) {
        char* token = strtok(input[i], " ");
        int col = 0;
        while (token != NULL && col < MAX_COLS) {
            strncpy(matrix[row][col], token, MAX_LENGTH - 1);
            matrix[row][col][MAX_LENGTH - 1] = '\\0';
            token = strtok(NULL, " ");
            col++;
        }
        row++;
    }

    // Allocate memory for result
    char* result = (char*)malloc(MAX_LENGTH * num_cols);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\\0';

    // Create transposed output
    for (int j = 0; j < num_cols; j++) {
        for (int i = 0; i < num_rows; i++) {
            strcat(result, matrix[i][j]);
            if (i < num_rows - 1) {
                strcat(result, " ");
            }
        }
        if (j < num_cols - 1) {
            strcat(result, "\\n");
        }
    }

    return result;
}

int main() {
    // Test cases
    char* test_cases[][3] = {
        {"name age", "alice 21", "ryan 30"},
        {"a b c", "1 2 3", "4 5 6"},
        {"x y", "p q", "m n"},
        {"test case", "some data"},
        {"col1 col2 col3", "val1 val2 val3"}
    };

    for (int i = 0; i < 5; i++) {
        printf("Input:\\n");
        for (int j = 0; j < 3 && test_cases[i][j] != NULL; j++) {
            printf("%s\\n", test_cases[i][j]);
        }

        char* result = transpose_file(test_cases[i], 3);
        if (result != NULL) {
            printf("Output:\\n%s\\n\\n", result);
            free(result);
        }
    }

    return 0;
}
