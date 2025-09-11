#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printTower(int n) {
    char** tower = buildTower(n);
    for (int i = 0; i < n; i++) {
        printf("%s\n", tower[i]);
    }
    printf("\n");
    // Free the memory
    for (int i = 0; i < n; i++) {
        free(tower[i]);
    }
    free(tower);
}

char** buildTower(int n) {
    char** tower = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        int spaces = n - i - 1;
        int stars = 2 * i + 1;
        tower[i] = getFloor(spaces, stars);
    }
    return tower;
}

char* getFloor(int spaces, int stars) {
    int length = spaces + stars + spaces;
    char* floor = (char*)malloc((length + 1) * sizeof(char));
    memset(floor, ' ', length);
    floor[length] = '\0';
    for (int i = spaces; i < spaces + stars; i++) {
        floor[i] = '*';
    }
    return floor;
}

int main() {
    printTower(3);
    printTower(6);
    printTower(1);
    printTower(2);
    printTower(5);
    return 0;
}