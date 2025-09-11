#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** buildTower(int floors) {
    char** tower = (char**)malloc(floors * sizeof(char*));
    int width = 2 * floors - 1;

    for (int i = 0; i < floors; i++) {
        int stars = 2 * i + 1;
        int spaces = (width - stars) / 2;
        tower[i] = (char*)malloc((width + 1) * sizeof(char));

        for (int j = 0; j < spaces; j++) {
            tower[i][j] = ' ';
        }
        for (int j = 0; j < stars; j++) {
            tower[i][spaces + j] = '*';
        }
        for (int j = spaces + stars; j < width; j++) {
            tower[i][j] = ' ';
        }
        tower[i][width] = '\0';
    }
    return tower;
}

void freeTower(char** tower, int floors) {
    for (int i = 0; i < floors; i++) {
        free(tower[i]);
    }
    free(tower);
}

int main() {
    int testCases[] = {1, 2, 3, 5, 6};
    int numCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numCases; i++) {
        int floors = testCases[i];
        char** result = buildTower(floors);
        for (int j = 0; j < floors; j++) {
            printf("%s\n", result[j]);
        }
        printf("\n");
        freeTower(result, floors);
    }
    return 0;
}