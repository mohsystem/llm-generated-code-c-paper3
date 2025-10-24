#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Frees the memory allocated for a tower.
 *
 * @param tower The tower to free.
 * @param n_floors The number of floors in the tower.
 */
void free_tower(char** tower, int n_floors) {
    if (tower == NULL) {
        return;
    }
    for (int i = 0; i < n_floors; ++i) {
        free(tower[i]);
    }
    free(tower);
}

/**
 * Builds a pyramid-shaped tower.
 *
 * @param n_floors The number of floors in the tower (must be positive).
 * @return A dynamically allocated array of strings representing the tower.
 *         The caller is responsible for freeing the memory using free_tower.
 *         Returns NULL if n_floors is not positive or if memory allocation fails.
 */
char** build_tower(int n_floors) {
    if (n_floors <= 0) {
        return NULL;
    }

    char** tower = (char**)malloc(n_floors * sizeof(char*));
    if (tower == NULL) {
        return NULL;
    }

    int tower_width = 2 * n_floors - 1;

    for (int i = 0; i < n_floors; ++i) {
        tower[i] = (char*)malloc((tower_width + 1) * sizeof(char));
        if (tower[i] == NULL) {
            // Cleanup previously allocated memory on failure
            free_tower(tower, i);
            return NULL;
        }

        int stars = 2 * i + 1;
        int padding = (tower_width - stars) / 2;

        // Fill leading padding
        if (padding > 0) {
            memset(tower[i], ' ', padding);
        }
        // Fill stars
        if (stars > 0) {
            memset(tower[i] + padding, '*', stars);
        }
        // Fill trailing padding
        if (padding > 0) {
            memset(tower[i] + padding + stars, ' ', padding);
        }
        // Null-terminate the string
        tower[i][tower_width] = '\0';
    }

    return tower;
}

void run_test_case(int floors) {
    printf("Tower with %d floors:\n", floors);
    char** tower = build_tower(floors);
    if (tower == NULL) {
        printf("[]\n");
    } else {
        printf("[\n");
        for (int i = 0; i < floors; ++i) {
            printf("  \"%s\"\n", tower[i]);
        }
        printf("]\n");
        free_tower(tower, floors);
    }
    printf("\n");
}

int main() {
    run_test_case(1);
    run_test_case(3);
    run_test_case(6);
    run_test_case(0);
    run_test_case(-5);
    return 0;
}