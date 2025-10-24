#include <stdio.h>
#include <limits.h>
#include <stddef.h>

typedef struct {
    int on;
    int off;
} Pair;

// Returns remaining passengers, or -1 for invalid input.
int countPassengers(const Pair* stops, size_t len) {
    if (stops == NULL && len != 0) {
        return -1;
    }
    long long occupancy = 0; // wider type to avoid overflow
    for (size_t i = 0; i < len; i++) {
        int on = stops[i].on;
        int off = stops[i].off;
        if (on < 0 || off < 0) {
            return -1;
        }
        long long next = occupancy + (long long)on - (long long)off;
        if (next < 0) {
            return -1; // invalid: more off than available
        }
        occupancy = next;
        if (occupancy > INT_MAX) {
            return -1; // prevent int overflow on return
        }
    }
    return (int)occupancy;
}

int main(void) {
    Pair t1[] = {{10, 0}, {3, 5}, {5, 8}}; // expected 5
    Pair t2[] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}}; // expected 15
    Pair t3[] = {{0, 0}}; // expected 0
    Pair t4[] = {{5, 0}, {0, 0}, {0, 0}}; // expected 5
    Pair t5[] = {{5, 0}, {2, 10}}; // invalid -> expected -1

    printf("%d\n", countPassengers(t1, sizeof(t1) / sizeof(t1[0])));
    printf("%d\n", countPassengers(t2, sizeof(t2) / sizeof(t2[0])));
    printf("%d\n", countPassengers(t3, sizeof(t3) / sizeof(t3[0])));
    printf("%d\n", countPassengers(t4, sizeof(t4) / sizeof(t4[0])));
    printf("%d\n", countPassengers(t5, sizeof(t5) / sizeof(t5[0])));

    return 0;
}