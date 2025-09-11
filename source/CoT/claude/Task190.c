
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000
#define MAX_LINE_LENGTH 1024

char* transpose_file(const char* filename, int* result_size) {
    char matrix[MAX_ROWS][MAX_COLS][MAX_LINE_LENGTH];
    int rows = 0, cols = 0;
    char* result = NULL;
    *result_size = 0;
    
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file\\n");
        return NULL;
    }
    
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, " \\n");
        cols = 0;
        while (token && cols < MAX_COLS) {
            strcpy(matrix[rows][cols], token);
            token = strtok(NULL, " \\n");
            cols++;
        }
        rows++;
        if (rows >= MAX_ROWS) break;
    }
    fclose(file);
    
    if (rows == 0 || cols == 0) {
        return NULL;
    }
    
    // Calculate required size for result
    int total_size = 0;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            total_size += strlen(matrix[i][j]) + 1; // +1 for space or newline
        }
    }
    
    result = (char*)malloc(total_size + 1); // +1 for null terminator
    if (!result) {
        return NULL;
    }
    
    char* current = result;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            int len = strlen(matrix[i][j]);
            memcpy(current, matrix[i][j], len);
            current += len;
            if (i < rows - 1) {
                *current = ' ';
            } else {
                *current = '\\n';
            }
            current++;
        }
    }
    *(current-1) = '\\0'; // Replace last newline with null terminator
    
    *result_size = current - result;
    return result;
}

int main() {
    // Test cases
    const char* test_files[] = {
        "file1.txt",
        "file2.txt",
        "file3.txt",
        "file4.txt",
        "file5.txt"
    };
    
    const char* test_contents[] = {
        "name age\\nalice 21\\nryan 30",
        "a b c\\n1 2 3\\nx y z",
        "col1 col2\\nval1 val2",
        "single",
        ""
    };
    
    for (int i = 0; i < 5; i++) {
        FILE* f = fopen(test_files[i], "w");
        if (f) {
            fprintf(f, "%s", test_contents[i]);
            fclose(f);
            
            int result_size;
            char* result = transpose_file(test_files[i], &result_size);
            
            printf("Test %d:\\n", i + 1);
            if (result) {
                printf("%s\\n", result);
                free(result);
            } else {
                printf("Empty or error\\n");
            }
        }
    }
    
    return 0;
}
