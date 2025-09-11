#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** towerBuilder(int nFloors, int* returnSize) {
    *returnSize = nFloors;
    char** tower = (char**)malloc(nFloors * sizeof(char*));
    for (int i = 0; i < nFloors; i++) {
        int len = (nFloors - 1 - i) + ((i * 2) + 1) + (nFloors - 1 - i);
        tower[i] = (char*)malloc((len + 1) * sizeof(char));
        memset(tower[i], ' ', len);
        tower[i][len] = '\0';
        for (int j = nFloors - 1 - i, k = 0; k < (i * 2) + 1; j++, k++) {
            tower[i][j] = '*';
        }
    }
    return tower;
}

int main() {
    int returnSize;
    char** tower = towerBuilder(3, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower[i]);
        free(tower[i]);
    }
    free(tower);

    tower = towerBuilder(6, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower[i]);
        free(tower[i]);
    }
    free(tower);

    return 0;
}