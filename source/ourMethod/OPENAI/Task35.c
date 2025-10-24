#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int on;
    int off;
} Stop;

int count_passengers(const Stop* stops, size_t n) {
    if (stops == NULL && n > 0) {
        return -1;
    }
    long long current = 0;
    for (size_t i = 0; i < n; ++i) {
        int on = stops[i].on;
        int off = stops[i].off;
        if (on < 0 || off < 0) {
            return -1;
        }
        // Check potential overflow on addition
        if (current > (long long)INT_MAX - (long long)on) {
            return -1;
        }
        current += on;
        if (off > current) {
            return -1;
        }
        current -= off;
    }
    if (current < 0 || current > INT_MAX) {
        return -1;
    }
    return (int)current;
}

int main(void) {
    Stop tc1[] = { {10,0}, {3,5}, {5,8} }; // 5
    Stop tc2[] = { {3,0}, {9,1}, {4,10}, {12,2}, {6,1}, {7,10} }; // 17
    Stop tc3[] = { {0,0} }; // 0
    Stop tc4[] = { {5,0}, {0,0}, {0,0} }; // 5
    Stop tc5[] = { {1000000,0}, {0,999999}, {0,0}, {0,1} }; // 0

    printf("%d\n", count_passengers(tc1, sizeof(tc1)/sizeof(tc1[0])));
    printf("%d\n", count_passengers(tc2, sizeof(tc2)/sizeof(tc2[0])));
    printf("%d\n", count_passengers(tc3, sizeof(tc3)/sizeof(tc3[0])));
    printf("%d\n", count_passengers(tc4, sizeof(tc4)/sizeof(tc4[0])));
    printf("%d\n", count_passengers(tc5, sizeof(tc5)/sizeof(tc5[0])));

    return 0;
}