#include <stdio.h>
#include <string.h>

#define MAX_ROWS 3
#define MAX_COLS 2
#define MAX_STR_LEN 10

void transpose(char input[MAX_ROWS][MAX_COLS][MAX_STR_LEN], char output[MAX_COLS][MAX_ROWS][MAX_STR_LEN], int rows, int cols) {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            strcpy(output[i][j], input[j][i]);
        }
    }
}

void print_transposed(char output[MAX_COLS][MAX_ROWS][MAX_STR_LEN], int rows, int cols) {
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            if (j > 0) printf(" ");
            printf("%s", output[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char input[MAX_ROWS][MAX_COLS][MAX_STR_LEN] = {
        {"name", "age"},
        {"alice", "21"},
        {"ryan", "30"}
    };

    char output[MAX_COLS][MAX_ROWS][MAX_STR_LEN];
    transpose(input, output, MAX_ROWS, MAX_COLS);
    print_transposed(output, MAX_ROWS, MAX_COLS);

    return 0;
}