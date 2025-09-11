#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** buildTower(int floors) {
    char** tower = (char**)malloc(floors * sizeof(char*));
    for (int i = 0; i < floors; i++) {
        int spaces = floors - i - 1;
        int stars = 2 * i + 1;
        tower[i] = (char*)malloc((2 * floors) * sizeof(char));
        memset(tower[i], ' ', 2 * floors - 1);
        memset(tower[i] + spaces, '*', stars);
        tower[i][2 * floors - 1] = '\0';
    }
    return tower;
}

int main() {
    int testCases[] = {1, 2, 3, 4, 5};
    for (int t = 0; t < sizeof(testCases) / sizeof(testCases[0]); t++) {
        int floors = testCases[t];
        char** result = buildTower(floors);
        for (int i = 0; i < floors; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
        printf("\n");
    }
    return 0;
}