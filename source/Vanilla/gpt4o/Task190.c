#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

void transposeContent(char lines[MAX_LINES][MAX_LENGTH], int lineCount) {
    char matrix[MAX_LINES][MAX_LINES][MAX_LENGTH];
    int numCols = 0;

    for (int i = 0; i < lineCount; i++) {
        int col = 0;
        char *token = strtok(lines[i], " ");
        while (token != NULL) {
            strcpy(matrix[i][col++], token);
            token = strtok(NULL, " ");
        }
        numCols = col;
    }

    for (int j = 0; j < numCols; j++) {
        for (int i = 0; i < lineCount; i++) {
            if (i > 0) printf(" ");
            printf("%s", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char lines[MAX_LINES][MAX_LENGTH] = {
        "name age",
        "alice 21",
        "ryan 30"
    };
    int lineCount = 3;

    transposeContent(lines, lineCount);

    return 0;
}