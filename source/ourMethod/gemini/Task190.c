#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_ROWS 100
#define MAX_COLS 100

char* transposeFile(const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        return NULL;
    }

    char lines[MAX_ROWS][MAX_LINE_LENGTH];
    int row = 0;
    while (fgets(lines[row], MAX_LINE_LENGTH, file) != NULL) {
        lines[row][strlen(lines[row]) - 1] = '\0'; // Remove trailing newline
        row++;
    }
    fclose(file);


    if (row == 0 || strlen(lines[0]) == 0) {
        return NULL;
    }

    char* result = (char*)malloc(MAX_ROWS * MAX_COLS * MAX_LINE_LENGTH * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, "");


    char* words[MAX_COLS];
    int cols = 0;
    char* token = strtok(lines[0], " ");
    while(token != NULL) {
        words[cols++] = token;
        token = strtok(NULL, " ");
    }

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < row; i++) {
            char* token = strtok(lines[i], " ");
            for(int k=0; k<j; ++k){
                token = strtok(NULL, " ");
            }
             strcat(result, token);
             if(i < row-1){
                strcat(result, " ");
             }
              lines[i][0] = '\0';
        }
        strcat(result, "\n");
    }

    result[strlen(result) - 1] = '\0'; // remove last 

    return result;

}

int main() {
    char* test1 = transposeFile("file1.txt");
    if (test1 != NULL) {
        printf("%s\n", test1);
        free(test1);
    }

    char* test2 = transposeFile("file2.txt");
    if (test2 != NULL) {
        printf("%s\n", test2);
        free(test2);
    }

    char* test3 = transposeFile("file3.txt");
    if (test3 != NULL) {
        printf("%s\n", test3);
        free(test3);
    }

    char* test4 = transposeFile("file4.txt");
    if (test4 != NULL) {
        printf("%s\n", test4);
        free(test4);
    }

    char* test5 = transposeFile("file5.txt");
    if (test5 != NULL) {
        printf("%s\n", test5);
        free(test5);
    }

    return 0;
}