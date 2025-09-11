#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** transposeContent(char** lines, int lineCount, int* resultCount) {
    if (lineCount == 0) {
        *resultCount = 0;
        return NULL;
    }
    
    int columnCount = 0;
    char* token = strtok(lines[0], " ");
    while (token) {
        columnCount++;
        token = strtok(NULL, " ");
    }
    
    char*** matrix = (char***)malloc(lineCount * sizeof(char**));
    for (int i = 0; i < lineCount; i++) {
        matrix[i] = (char**)malloc(columnCount * sizeof(char*));
        int col = 0;
        char* token = strtok(lines[i], " ");
        while (token) {
            matrix[i][col++] = token;
            token = strtok(NULL, " ");
        }
    }
    
    char** result = (char**)malloc(columnCount * sizeof(char*));
    for (int i = 0; i < columnCount; i++) {
        result[i] = (char*)malloc(lineCount * 256 * sizeof(char)); // Assuming max token length
        strcpy(result[i], matrix[0][i]);
        for (int j = 1; j < lineCount; j++) {
            strcat(result[i], " ");
            strcat(result[i], matrix[j][i]);
        }
    }
    
    *resultCount = columnCount;
    
    for (int i = 0; i < lineCount; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return result;
}

int main() {
    char* lines[] = {
        "name age",
        "alice 21",
        "ryan 30"
    };
    int lineCount = sizeof(lines) / sizeof(lines[0]);
    int resultCount;
    char** transposed = transposeContent(lines, lineCount, &resultCount);
    
    for (int i = 0; i < resultCount; i++) {
        printf("%s\n", transposed[i]);
        free(transposed[i]);
    }
    free(transposed);
    
    // Additional test cases
    char* test1[] = {"a b", "c d"};
    lineCount = sizeof(test1) / sizeof(test1[0]);
    transposed = transposeContent(test1, lineCount, &resultCount);
    for (int i = 0; i < resultCount; i++) {
        printf("%s\n", transposed[i]);
        free(transposed[i]);
    }
    free(transposed); // Should print [a c, b d]

    char* test2[] = {"1 2 3", "4 5 6", "7 8 9"};
    lineCount = sizeof(test2) / sizeof(test2[0]);
    transposed = transposeContent(test2, lineCount, &resultCount);
    for (int i = 0; i < resultCount; i++) {
        printf("%s\n", transposed[i]);
        free(transposed[i]);
    }
    free(transposed); // Should print [1 4 7, 2 5 8, 3 6 9]

    char* test3[] = {"onlyone"};
    lineCount = sizeof(test3) / sizeof(test3[0]);
    transposed = transposeContent(test3, lineCount, &resultCount);
    for (int i = 0; i < resultCount; i++) {
        printf("%s\n", transposed[i]);
        free(transposed[i]);
    }
    free(transposed); // Should print [onlyone]

    char* test4[] = {};
    lineCount = sizeof(test4) / sizeof(test4[0]);
    transposed = transposeContent(test4, lineCount, &resultCount);
    for (int i = 0; i < resultCount; i++) {
        printf("%s\n", transposed[i]);
        free(transposed[i]);
    }
    free(transposed); // Should print []

    char* test5[] = {"x y z"};
    lineCount = sizeof(test5) / sizeof(test5[0]);
    transposed = transposeContent(test5, lineCount, &resultCount);
    for (int i = 0; i < resultCount; i++) {
        printf("%s\n", transposed[i]);
        free(transposed[i]);
    }
    free(transposed); // Should print [x, y, z]

    return 0;
}