#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** build_tower(int n_floors, int* len) {
    if (n_floors <= 0) {
        fprintf(stderr, "Number of floors must be a positive integer\n");
        exit(EXIT_FAILURE);
    }

    char** tower = malloc(n_floors * sizeof(char*));
    if (tower == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n_floors; i++) {
        int spaces = n_floors - i - 1;
        int stars = 2 * i + 1;
        int total_len = spaces + stars + spaces + 1; // +1 for null terminator
        tower[i] = malloc(total_len * sizeof(char));
        if (tower[i] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
        snprintf(tower[i], total_len, "%*s%*s%*s", spaces, "", stars, "*", spaces, "");
    }

    *len = n_floors;
    return tower;
}

int main() {
    int len3, len6;
    char** tower3 = build_tower(3, &len3);
    char** tower6 = build_tower(6, &len6);

    for (int i = 0; i < len3; i++) {
        printf("%s\n", tower3[i]);
        free(tower3[i]);
    }
    free(tower3);

    for (int i = 0; i < len6; i++) {
        printf("%s\n", tower6[i]);
        free(tower6[i]);
    }
    free(tower6);

    return 0;
}