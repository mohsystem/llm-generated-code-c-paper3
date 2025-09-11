
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000
#define MAX_LINE_LENGTH 1024

char* transpose_file(const char* filename) {
    char matrix[MAX_ROWS][MAX_COLS][MAX_LINE_LENGTH];
    int rows = 0, cols = 0;
    char* result = NULL;
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file\\n");
        return NULL;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, " \\n");
        cols = 0;
        while (token && cols < MAX_COLS) {
            strncpy(matrix[rows][cols], token, MAX_LINE_LENGTH - 1);
            matrix[rows][cols][MAX_LINE_LENGTH - 1] = '\\0';
            token = strtok(NULL, " \\n");
            cols++;
        }
        if (cols > 0) rows++;
        if (rows >= MAX_ROWS) break;
    }
    fclose(file);
    
    if (rows == 0) {
        return NULL;
    }
    
    // Calculate required buffer size
    size_t total_size = 0;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            total_size += strlen(matrix[i][j]) + 1; // +1 for space or newline
        }
    }
    
    result = (char*)malloc(total_size + 1); // +1 for null terminator
    if (!result) {
        return NULL;
    }
    
    char* ptr = result;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            size_t len = strlen(matrix[i][j]);
            memcpy(ptr, matrix[i][j], len);
            ptr += len;
            if (i < rows - 1) {
                *ptr++ = ' ';
            }
        }
        if (j < cols - 1) {
            *ptr++ = '\\n';
        }
    }
    *ptr = '\\0';
    
    return result;
}

int main() {
    FILE* outFile;
    
    // Test Case 1: Normal case
    outFile = fopen("test1.txt", "w");
    fprintf(outFile, "name age\\nalice 21\\nryan 30");
    fclose(outFile);
    char* result1 = transpose_file("test1.txt");
    if (result1) {
        printf("Test 1:\\n%s\\n", result1);
        free(result1);
    }
    
    // Test Case 2: Empty file
    outFile = fopen("test2.txt", "w");
    fclose(outFile);
    char* result2 = transpose_file("test2.txt");
    printf("Test 2: %s\\n", result2 ? result2 : "NULL");
    if (result2) free(result2);
    
    // Test Case 3: Single line
    outFile = fopen("test3.txt", "w");
    fprintf(outFile, "a b c");
    fclose(outFile);
    char* result3 = transpose_file("test3.txt");
    if (result3) {
        printf("Test 3:\\n%s\\n", result3);
        free(result3);
    }
    
    // Test Case 4: Single column
    outFile = fopen("test4.txt", "w");
    fprintf(outFile, "a\\nb\\nc");
    fclose(outFile);
    char* result4 = transpose_file("test4.txt");
    if (result4) {
        printf("Test 4:\\n%s\\n", result4);
        free(result4);
    }
    
    // Test Case 5: Multiple spaces
    outFile = fopen("test5.txt", "w");
    fprintf(outFile, "a  b\\nc  d");
    fclose(outFile);
    char* result5 = transpose_file("test5.txt");
    if (result5) {
        printf("Test 5:\\n%s\\n", result5);
        free(result5);
    }
    
    return 0;
}
