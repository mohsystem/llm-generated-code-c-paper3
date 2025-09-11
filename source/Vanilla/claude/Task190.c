
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_LENGTH 1000

char* transpose(char** input, int rows) {
    if (rows == 0) return NULL;
    
    // Split input into matrix
    char matrix[MAX_ROWS][MAX_COLS][100];
    int cols[MAX_ROWS] = {0};
    int maxCols = 0;
    
    for (int i = 0; i < rows; i++) {
        char* token = strtok(input[i], " ");
        while (token != NULL) {
            strcpy(matrix[i][cols[i]], token);
            cols[i]++;
            if (cols[i] > maxCols) maxCols = cols[i];
            token = strtok(NULL, " ");
        }
    }
    
    // Allocate result buffer
    char* result = (char*)malloc(MAX_LENGTH * maxCols);
    result[0] = '\\0';
    char line[MAX_LENGTH];
    
    // Create transposed output
    for (int j = 0; j < maxCols; j++) {
        line[0] = '\\0';
        for (int i = 0; i < rows; i++) {
            if (j < cols[i]) {
                strcat(line, matrix[i][j]);
            }
            if (i != rows - 1) {
                strcat(line, " ");
            }
        }
        strcat(line, "\\n");
        strcat(result, line);
    }
    
    return result;
}

int main() {
    char* test_cases[][MAX_ROWS] = {
        {"name age", "alice 21", "ryan 30"},
        {"a b c", "1 2 3", "x y z"},
        {"col1 col2", "val1 val2"},
        {"single"},
        {"header1 header2 header3", "data1 data2 data3"}
    };
    
    int test_rows[] = {3, 3, 2, 1, 2};
    
    for (int t = 0; t < 5; t++) {
        printf("Test case %d:\\n", t + 1);
        printf("Input:\\n");
        for (int i = 0; i < test_rows[t]; i++) {
            printf("%s\\n", test_cases[t][i]);
        }
        printf("Output:\\n");
        
        // Create copy of input as strtok modifies original string
        char* input_copy[MAX_ROWS];
        for (int i = 0; i < test_rows[t]; i++) {
            input_copy[i] = strdup(test_cases[t][i]);
        }
        
        char* result = transpose(input_copy, test_rows[t]);
        printf("%s\\n", result);
        
        // Free allocated memory
        free(result);
        for (int i = 0; i < test_rows[t]; i++) {
            free(input_copy[i]);
        }
    }
    
    return 0;
}
