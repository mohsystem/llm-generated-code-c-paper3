#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void towerBuilder(int nFloors, char** tower) {
    for (int i = 0; i < nFloors; i++) {
        int spaces = nFloors - i - 1;
        int stars = 2 * i + 1;
        int length = 2 * nFloors - 1;
        tower[i] = (char*)malloc((length + 1) * sizeof(char));
        memset(tower[i], ' ', length);
        tower[i][length] = '\0';
        for (int j = 0; j < stars; j++) {
            tower[i][spaces + j] = '*';
        }
    }
}

int main() {
    for (int i = 1; i <= 5; i++) {
        char** tower = (char**)malloc(i * sizeof(char*));
        towerBuilder(i, tower);
        printf("Tower with %d floors:\n", i);
        for (int j = 0; j < i; j++) {
            printf("%s\n", tower[j]);
            free(tower[j]);
        }
        free(tower);
        printf("\n");
    }
    return 0;
}