#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming maximum line length and number of columns
#define MAX_LINE_LENGTH 1024
#define MAX_COLUMNS 100

char* transposeFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        char* error_msg = strdup("Error opening file");
        return error_msg;
    }

    char line[MAX_LINE_LENGTH];
    char data[MAX_COLUMNS][MAX_LINE_LENGTH];
    int num_rows = 0;
    int num_cols = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char* token = strtok(line, " \n");
        int col = 0;
        while (token != NULL) {
            strcpy(data[col++], token);
            token = strtok(NULL, " \n");
        }
        num_rows++;
        num_cols = col; 
    }
    fclose(file);

    char* result = (char*)malloc(MAX_LINE_LENGTH * MAX_COLUMNS * sizeof(char));
    char* current_pos = result;

    for (int j = 0; j < num_cols; j++) {
        for (int i = 0; i < num_rows; i++) {
            strcpy(current_pos, data[j][i]);
            current_pos += strlen(data[j][i]);

             if (i < num_rows - 1) {
                *current_pos++ = ' ';
            }
        }
        *current_pos++ = '\n';
    }
    *current_pos = '\0';


    return result;
}

int main() {
    char* test1 = transposeFile("file1.txt");
    printf("%s", test1);
    free(test1);

    char* test2 = transposeFile("file2.txt");
    printf("%s", test2);
    free(test2);

    char* test3 = transposeFile("file3.txt");
    printf("%s", test3);
    free(test3);

    char* test4 = transposeFile("file4.txt");
    printf("%s", test4);
    free(test4);

    char* test5 = transposeFile("file5.txt");
    printf("%s", test5);
    free(test5);


    return 0;
}