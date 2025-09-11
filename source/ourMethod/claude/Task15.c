
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** towerBuilder(unsigned int nFloors) {
    if (nFloors == 0) {
        return NULL;
    }
    
    size_t maxWidth = 2 * nFloors - 1;
    char** tower = (char**)malloc(nFloors * sizeof(char*));
    if (!tower) {
        return NULL;
    }
    
    for (size_t i = 0; i < nFloors; i++) {
        tower[i] = (char*)malloc((maxWidth + 1) * sizeof(char));
        if (!tower[i]) {
            // Clean up previously allocated memory
            for (size_t j = 0; j < i; j++) {
                free(tower[j]);
            }
            free(tower);
            return NULL;
        }
        
        size_t stars = 2 * i + 1;
        size_t spaces = (maxWidth - stars) / 2;
        
        memset(tower[i], ' ', maxWidth);
        memset(tower[i] + spaces, '*', stars);
        tower[i][maxWidth] = '\\0';
    }
    
    return tower;
}

void freeTower(char** tower, unsigned int nFloors) {
    if (tower) {
        for (size_t i = 0; i < nFloors; i++) {
            free(tower[i]);
        }
        free(tower);
    }
}

int main() {
    unsigned int tests[] = {1, 2, 3, 4, 6};
    size_t numTests = sizeof(tests) / sizeof(tests[0]);
    
    for (size_t i = 0; i < numTests; i++) {
        printf("Tower with %u floors:\\n", tests[i]);
        char** tower = towerBuilder(tests[i]);
        if (tower) {
            for (size_t j = 0; j < tests[i]; j++) {
                printf("%s\\n", tower[j]);
            }
            printf("\\n");
            freeTower(tower, tests[i]);
        }
    }
    
    return 0;
}
