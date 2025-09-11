#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buildTower(int floors, char*** tower) {
    *tower = (char**)malloc(floors * sizeof(char*));
    for (int i = 0; i < floors; i++) {
        int numSpaces = floors - i - 1;
        int numStars = 2 * i + 1;
        (*tower)[i] = (char*)malloc((numSpaces + numStars + numSpaces + 1) * sizeof(char));
        memset((*tower)[i], ' ', numSpaces);
        memset((*tower)[i] + numSpaces, '*', numStars);
        memset((*tower)[i] + numSpaces + numStars, ' ', numSpaces);
        (*tower)[i][numSpaces + numStars + numSpaces] = '\0';
    }
}

int main() {
    int testCases[] = {1, 2, 3, 4, 5};
    char** tower;
    for (int j = 0; j < 5; j++) {
        int floors = testCases[j];
        printf("Tower with %d floors:\n", floors);
        buildTower(floors, &tower);
        for (int i = 0; i < floors; i++) {
            printf("%s\n", tower[i]);
            free(tower[i]);
        }
        free(tower);
        printf("\n");
    }
    return 0;
}