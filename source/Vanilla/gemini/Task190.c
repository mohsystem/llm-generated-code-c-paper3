#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* transposeFile(const char* filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        return NULL; 
    }

    char line[1024];
    char ***data = NULL;
    int num_rows = 0;
    int num_cols = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        num_rows++;
        data = realloc(data, num_rows * sizeof(char**));
        data[num_rows - 1] = NULL;
        int col = 0;
        char *token = strtok(line, " \n");
        while (token != NULL) {
            if (num_rows == 1) {
                num_cols++;
            }
            data[num_rows - 1] = realloc(data[num_rows - 1], (col + 1) * sizeof(char*));
            data[num_rows - 1][col] = strdup(token);
            token = strtok(NULL, " \n");
            col++;
        }

        if (num_rows > 1 && col != num_cols) {
            fprintf(stderr, "Inconsistent number of columns.\n");
             // Handle the error as needed (e.g., free allocated memory and return)
             fclose(file);
             return NULL;
        }
    }
    fclose(file);


    char *result = NULL;
    size_t result_len = 0;

    for (int j = 0; j < num_cols; j++) {
        for (int i = 0; i < num_rows; i++) {
            size_t word_len = strlen(data[i][j]);
            result = realloc(result, result_len + word_len + 2); // +2 for space/newline and null terminator
            memcpy(result + result_len, data[i][j], word_len);
            result_len += word_len;

            if (i < num_rows - 1) {
                result[result_len++] = ' ';
            }
        }
        if (j < num_cols - 1) {
            result[result_len++] = '\n';
        }
    }
    result[result_len] = '\0';

    // Free allocated memory
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++) {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);
    return result;
}

int main() {
    char *result1 = transposeFile("file1.txt");
    printf("%s\n", result1 ? result1 : "Error or empty file");
    free(result1);

    char *result2 = transposeFile("file2.txt");
    printf("%s\n", result2 ? result2 : "Error or empty file");
    free(result2);


    char *result3 = transposeFile("file3.txt");
    printf("%s\n", result3 ? result3 : "Error or empty file");
    free(result3);

    char *result4 = transposeFile("file4.txt");
    printf("%s\n", result4 ? result4 : "Error or empty file");
    free(result4);


    char *result5 = transposeFile("file5.txt");
    printf("%s\n", result5 ? result5 : "Error or empty file");
    free(result5);
    return 0;
}