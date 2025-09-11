#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** towerBuilder(int nFloors) {
    char** tower = (char**)malloc(nFloors * sizeof(char*));
    int width = 2 * nFloors - 1;

    for (int i = 1; i <= nFloors; i++) {
        int numStars = 2 * i - 1;
        int numSpaces = (width - numStars) / 2;
        tower[i - 1] = (char*)malloc((width + 1) * sizeof(char)); 
        for (int j = 0; j < numSpaces; j++) {
            tower[i - 1][j] = ' ';
        }
        for (int j = 0; j < numStars; j++) {
            tower[i - 1][numSpaces + j] = '*';
        }
        for (int j = 0; j < numSpaces; j++) {
            tower[i - 1][numSpaces + numStars + j] = ' ';
        }
        tower[i - 1][width] = '\0'; 
    }
    return tower;
}

int main() {
    int testCases[] = {1, 2, 3, 4, 6};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        char** tower = towerBuilder(testCases[i]);
        for (int j = 0; j < testCases[i]; j++) {
            printf("%s\n", tower[j]);
            free(tower[j]);
        }
        free(tower);
        printf("\n");
    }
    return 0;
}