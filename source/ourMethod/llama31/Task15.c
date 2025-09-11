#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printTower(int nFloors) {
    for (int i = 0; i < nFloors; ++i) {
        int spaces = nFloors - i - 1;
        int stars = 2 * i + 1;
        for (int j = 0; j < spaces; ++j) {
            printf(" ");
        }
        for (int j = 0; j < stars; ++j) {
            printf("*");
        }
        for (int j = 0; j < spaces; ++j) {
            printf(" ");
        }
        printf("\n");
    }
}

int main() {
    for (int i = 1; i <= 6; ++i) {
        printTower(i);
        printf("\n");
    }
    return 0;
}