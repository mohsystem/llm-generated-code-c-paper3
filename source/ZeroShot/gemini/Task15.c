#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **towerBuilder(int nFloors) {
    char **tower = (char **)malloc(nFloors * sizeof(char *));
    for (int i = 1; i <= nFloors; i++) {
        int numStars = 2 * i - 1;
        int numSpaces = nFloors - i;
        int floorLength = numStars + 2 * numSpaces;
        tower[i - 1] = (char *)malloc((floorLength + 1) * sizeof(char)); 
        for (int j = 0; j < numSpaces; j++) {
            tower[i - 1][j] = ' ';
        }
        for (int j = numSpaces; j < numSpaces + numStars; j++) {
            tower[i - 1][j] = '*';
        }
        for (int j = numSpaces + numStars; j < floorLength; j++) {
            tower[i - 1][j] = ' ';
        }
        tower[i - 1][floorLength] = '\0';
    }
    return tower;
}

int main() {
    int testCases[] = {1, 2, 3, 4, 6};
    int numTestCases = sizeof(testCases) / sizeof(testCases[0]);

    for (int i = 0; i < numTestCases; i++) {
        int nFloors = testCases[i];
        char **tower = towerBuilder(nFloors);
        for (int j = 0; j < nFloors; j++) {
            printf("%s\n", tower[j]);
            free(tower[j]);
        }
        free(tower);
        printf("\n");
    }

    return 0;
}