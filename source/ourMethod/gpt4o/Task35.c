#include <stdio.h>

int remaining_passengers(int stops[][2], int size) {
    int passengers = 0;
    for (int i = 0; i < size; ++i) {
        passengers += stops[i][0];
        passengers -= stops[i][1];
    }
    return passengers;
}

int main() {
    int stops1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    printf("%d\n", remaining_passengers(stops1, 3)); // 5

    int stops2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    printf("%d\n", remaining_passengers(stops2, 6)); // 17

    int stops3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    printf("%d\n", remaining_passengers(stops3, 6)); // 21

    int stops4[][2] = {{0, 0}};
    printf("%d\n", remaining_passengers(stops4, 1)); // 0

    int stops5[][2] = {{10, 0}, {5, 5}, {5, 10}};
    printf("%d\n", remaining_passengers(stops5, 3)); // 0

    return 0;
}