#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** buildTower(int floors, int* returnSize) {
    char** tower = (char**)malloc(floors * sizeof(char*));
    for (int i = 0; i < floors; i++) {
        int spaces = floors - i - 1;
        int stars = i * 2 + 1;
        tower[i] = (char*)malloc((2 * floors) * sizeof(char));
        memset(tower[i], ' ', 2 * floors - 1);
        for (int j = spaces; j < spaces + stars; j++) {
            tower[i][j] = '*';
        }
        tower[i][2 * floors - 1] = '\0';
    }
    *returnSize = floors;
    return tower;
}

void freeTower(char** tower, int size) {
    for (int i = 0; i < size; i++) {
        free(tower[i]);
    }
    free(tower);
}

int main() {
    int sizes[5];
    int testCases[] = {3, 6, 1, 4, 0};

    for (int i = 0; i < 5; i++) {
        int floors = testCases[i];
        char** tower = buildTower(floors, &sizes[i]);
        for (int j = 0; j < sizes[i]; j++) {
            printf("%s\n", tower[j]);
        }
        printf("\n");
        freeTower(tower, sizes[i]);
    }

    return 0;
}