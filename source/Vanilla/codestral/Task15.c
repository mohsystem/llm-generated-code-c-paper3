#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** buildTower(int nFloors, int* returnSize) {
    char** tower = malloc(nFloors * sizeof(char*));
    *returnSize = nFloors;
    for (int i = 0; i < nFloors; i++) {
        tower[i] = malloc((2 * nFloors) * sizeof(char));
        memset(tower[i], ' ', 2 * nFloors - 1);
        tower[i][2 * nFloors - 1] = '\0';
        for (int j = nFloors - i - 1; j < nFloors + i; j++) {
            tower[i][j] = '*';
        }
    }
    return tower;
}

int main() {
    int returnSize;
    char** tower3 = buildTower(3, &returnSize);
    char** tower6 = buildTower(6, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower3[i]);
        free(tower3[i]);
    }
    free(tower3);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower6[i]);
        free(tower6[i]);
    }
    free(tower6);
    return 0;
}