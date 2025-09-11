#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** buildTower(int n, int* returnSize) {
    char** tower = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        tower[i] = malloc((2 * n) * sizeof(char));
        memset(tower[i], ' ', 2 * n - 1);
        tower[i][n - i - 1] = '\0';
        memset(tower[i] + n - i - 1, '*', 2 * i + 1);
    }
    *returnSize = n;
    return tower;
}

int main() {
    int returnSize;
    char** tower = buildTower(3, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower[i]);
        free(tower[i]);
    }
    free(tower);
    return 0;
}