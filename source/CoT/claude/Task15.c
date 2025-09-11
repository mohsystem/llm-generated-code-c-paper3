
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** buildTower(int floors, int* size) {
    if (floors <= 0) {
        *size = 0;
        return NULL;
    }
    
    *size = floors;
    int width = 2 * floors - 1;
    char** tower = (char**)malloc(floors * sizeof(char*));
    
    for (int i = 0; i < floors; i++) {
        tower[i] = (char*)malloc((width + 1) * sizeof(char));
        int stars = 2 * i + 1;
        int spaces = (width - stars) / 2;
        
        int pos = 0;
        for (int j = 0; j < spaces; j++) tower[i][pos++] = ' ';
        for (int j = 0; j < stars; j++) tower[i][pos++] = '*';
        for (int j = 0; j < spaces; j++) tower[i][pos++] = ' ';
        tower[i][width] = '\\0';
    }
    return tower;
}

void freeTower(char** tower, int size) {
    if (tower) {
        for (int i = 0; i < size; i++) {
            free(tower[i]);
        }
        free(tower);
    }
}

int main() {
    int testCases[] = {1, 2, 3, 4, 6};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        int size;
        printf("Tower with %d floors:\\n", testCases[i]);
        char** tower = buildTower(testCases[i], &size);
        
        for (int j = 0; j < size; j++) {
            printf("%s\\n", tower[j]);
        }
        printf("\\n");
        
        freeTower(tower, size);
    }
    return 0;
}
