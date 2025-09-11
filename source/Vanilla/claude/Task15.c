
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** buildTower(int floors) {
    char** tower = (char**)malloc(floors * sizeof(char*));
    int width = 2 * floors - 1;
    
    for(int i = 0; i < floors; i++) {
        tower[i] = (char*)malloc((width + 1) * sizeof(char));
        int stars = 2 * i + 1;
        int spaces = (width - stars) / 2;
        
        int pos = 0;
        for(int j = 0; j < spaces; j++) tower[i][pos++] = ' ';
        for(int j = 0; j < stars; j++) tower[i][pos++] = '*';
        for(int j = 0; j < spaces; j++) tower[i][pos++] = ' ';
        tower[i][width] = '\\0';
    }
    return tower;
}

int main() {
    int tests[] = {1, 2, 3, 4, 6};
    int num_tests = 5;
    
    for(int t = 0; t < num_tests; t++) {
        int floors = tests[t];
        printf("Tower with %d floors:\\n", floors);
        
        char** tower = buildTower(floors);
        for(int i = 0; i < floors; i++) {
            printf("%s\\n", tower[i]);
            free(tower[i]);
        }
        free(tower);
        printf("\\n");
    }
    return 0;
}
