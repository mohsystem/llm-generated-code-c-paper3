#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ** towerBuilder(int nFloors, int *returnSize) {
    char **tower = (char **)malloc(nFloors * sizeof(char *));
    *returnSize = nFloors;

    for (int i = 1; i <= nFloors; i++) {
        int stars = 2 * i - 1;
        int spaces = nFloors - i;
        int totalLen = 2 * nFloors -1;
        tower[i - 1] = (char *)malloc(totalLen * sizeof(char) + 1); 

        for (int j = 0; j < spaces; j++) {
            tower[i - 1][j] = ' ';
        }
        for (int j = spaces; j < spaces + stars; j++) {
            tower[i - 1][j] = '*';
        }
        for (int j = spaces + stars; j < totalLen; j++) {
            tower[i - 1][j] = ' ';
        }
        tower[i-1][totalLen] = '\0';
    }
    return tower;
}

int main() {
    int returnSize;

    char **tower1 = towerBuilder(1, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower1[i]);
        free(tower1[i]);
    }
    free(tower1);
    printf("\n");

    char **tower3 = towerBuilder(3, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower3[i]);
        free(tower3[i]);
    }
    free(tower3);
    printf("\n");

    char **tower6 = towerBuilder(6, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower6[i]);
        free(tower6[i]);
    }
    free(tower6);
    printf("\n");

    char **tower0 = towerBuilder(0, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower0[i]);
        free(tower0[i]);
    }
    free(tower0);
    printf("\n");

    char **tower10 = towerBuilder(10, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower10[i]);
        free(tower10[i]);
    }
    free(tower10);
    printf("\n");


    return 0;
}