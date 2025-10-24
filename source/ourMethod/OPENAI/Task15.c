#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_FLOORS 1000

typedef struct {
    char **rows;
    size_t count;
    int error; /* 0 = OK, nonzero = error */
} TowerResult;

static void free_tower(TowerResult *res) {
    if (res == NULL) return;
    if (res->rows != NULL) {
        for (size_t i = 0; i < res->count; i++) {
            free(res->rows[i]);
            res->rows[i] = NULL;
        }
        free(res->rows);
        res->rows = NULL;
    }
    res->count = 0;
    res->error = 0;
}

TowerResult build_tower(int floors) {
    TowerResult result;
    result.rows = NULL;
    result.count = 0;
    result.error = 0;

    if (floors < 1 || floors > MAX_FLOORS) {
        result.error = 1; /* invalid input */
        return result;
    }

    size_t n = (size_t)floors;
    size_t width = 2 * n - 1;

    result.rows = (char **)calloc(n, sizeof(char *));
    if (result.rows == NULL) {
        result.error = 2; /* allocation failure */
        return result;
    }

    for (size_t i = 1; i <= n; i++) {
        size_t spaces = n - i;
        size_t stars = 2 * i - 1;

        char *line = (char *)malloc(width + 1);
        if (line == NULL) {
            result.error = 2;
            result.count = i - 1;
            free_tower(&result);
            return result;
        }

        size_t pos = 0;
        for (size_t s = 0; s < spaces && pos < width; s++) line[pos++] = ' ';
        for (size_t st = 0; st < stars && pos < width; st++) line[pos++] = '*';
        for (size_t s = 0; s < spaces && pos < width; s++) line[pos++] = ' ';
        if (pos != width) {
            /* internal error safeguard */
            free(line);
            result.error = 3;
            result.count = i - 1;
            free_tower(&result);
            return result;
        }
        line[width] = '\0';
        result.rows[i - 1] = line;
    }

    result.count = n;
    result.error = 0;
    return result;
}

static void print_tower(const TowerResult *res) {
    if (res == NULL || res->error != 0) {
        printf("Error: invalid tower result\n");
        return;
    }
    printf("[\n");
    for (size_t i = 0; i < res->count; i++) {
        printf("  \"%s\"%s\n", res->rows[i], (i + 1 < res->count) ? "," : "");
    }
    printf("]\n");
}

int main(void) {
    int tests[5] = {1, 3, 6, 2, 0};
    for (size_t ti = 0; ti < 5; ti++) {
        int t = tests[ti];
        printf("Test floors=%d\n", t);
        TowerResult res = build_tower(t);
        if (res.error != 0) {
            printf("Error: floors must be between 1 and %d or memory allocation failed\n", MAX_FLOORS);
        } else {
            print_tower(&res);
        }
        free_tower(&res);
        printf("\n");
    }
    return 0;
}