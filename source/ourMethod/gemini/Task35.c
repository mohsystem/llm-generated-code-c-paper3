#include <stdio.h>

int people_on_bus(int stops[][2], int num_stops) {
    int people = 0;
    for (int i = 0; i < num_stops; i++) {
        people += stops[i][0] - stops[i][1];
    }
    return people;
}

int main() {
    int stops1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    printf("%d\n", people_on_bus(stops1, 3)); // 2

    int stops2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    printf("%d\n", people_on_bus(stops2, 6)); // 17

    int stops3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    printf("%d\n", people_on_bus(stops3, 6)); // 21

    int stops4[][2] = {{0, 0}};
    printf("%d\n", people_on_bus(stops4, 1)); // 0

    int stops5[][2] = {{1, 0}, {2, 0}, {3, 0}};
    printf("%d\n", people_on_bus(stops5, 3)); // 6
    return 0;
}