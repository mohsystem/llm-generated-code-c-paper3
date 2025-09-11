#include <stdio.h>

int peopleOnBus(int busStops[][2], int size) {
    int peopleOnBus = 0;
    for (int i = 0; i < size; i++) {
        peopleOnBus += busStops[i][0] - busStops[i][1];
    }
    return peopleOnBus;
}

int main() {
    int busStops1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    printf("%d\n", peopleOnBus(busStops1, 3)); // Output: 5

    int busStops2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    printf("%d\n", peopleOnBus(busStops2, 6)); // Output: 17

    int busStops3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    printf("%d\n", peopleOnBus(busStops3, 6)); // Output: 21

    int busStops4[][2] = {{0, 0}};
    printf("%d\n", peopleOnBus(busStops4, 1)); // Output: 0

    int busStops5[][2] = {{10, 0}, {0, 5}, {5, 5}};
    printf("%d\n", peopleOnBus(busStops5, 3)); // Output: 5

    return 0;
}