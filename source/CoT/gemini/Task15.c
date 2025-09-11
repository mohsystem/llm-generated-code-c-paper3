#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **towerBuilder(int nFloors, int *returnSize) {
    *returnSize = nFloors;
    char **tower = (char **)malloc(nFloors * sizeof(char *));
    int width = 2 * nFloors - 1;

    for (int i = 1; i <= nFloors; i++) {
        int numStars = 2 * i - 1;
        int numSpaces = (width - numStars) / 2;
        tower[i - 1] = (char *)malloc((width + 1) * sizeof(char));
        memset(tower[i - 1], ' ', width);
        memset(tower[i - 1] + numSpaces, '*', numStars);
        tower[i - 1][width] = '\0';
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

    char **tower2 = towerBuilder(2, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower2[i]);
        free(tower2[i]);
    }
    free(tower2);
    printf("\n");

    char **tower3 = towerBuilder(3, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower3[i]);
        free(tower3[i]);
    }
    free(tower3);
    printf("\n");

        char **tower4 = towerBuilder(4, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower4[i]);
        free(tower4[i]);
    }
    free(tower4);
    printf("\n");

    char **tower6 = towerBuilder(6, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", tower6[i]);
        free(tower6[i]);
    }
    free(tower6);


    return 0;
}