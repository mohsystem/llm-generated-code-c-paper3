#include <stdio.h>

int remainingPassengers(int busStops[][2], int size) {
    int passengers = 0;
    for (int i = 0; i < size; ++i) {
        passengers += busStops[i][0];
        passengers -= busStops[i][1];
    }
    return passengers;
}

int main() {
    int busStops1[][2] = {{10, 0}, {3, 5}, {5, 8}, {2, 2}, {1, 0}};
    printf("%d\n", remainingPassengers(busStops1, 5)); // Output: 6

    int busStops2[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    printf("%d\n", remainingPassengers(busStops2, 6)); // Output: 21

    int busStops3[][2] = {{0, 0}, {5, 2}, {2, 5}, {4, 3}};
    printf("%d\n", remainingPassengers(busStops3, 4)); // Output: 1

    int busStops4[][2] = {{2, 0}, {3, 1}, {8, 2}, {4, 2}};
    printf("%d\n", remainingPassengers(busStops4, 4)); // Output: 12

    int busStops5[][2] = {{0, 0}};
    printf("%d\n", remainingPassengers(busStops5, 1)); // Output: 0

    return 0;
}