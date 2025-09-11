#include <stdio.h>

int peopleOnBus(int stops[][2], int numStops) {
    int people = 0;
    for (int i = 0; i < numStops; i++) {
        people += stops[i][0] - stops[i][1];
    }
    return people;
}

int main() {
    int stops1[][2] = {{10, 0}, {3, 5}, {2, 5}};
    printf("%d\n", peopleOnBus(stops1, 3)); // Output: 2

    int stops2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    printf("%d\n", peopleOnBus(stops2, 6)); // Output: 17

    int stops3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    printf("%d\n", peopleOnBus(stops3, 6)); // Output: 17

    int stops4[][2] = {{1, 0}, {2, 0}, {3, 0}};
    printf("%d\n", peopleOnBus(stops4, 3));

    int stops5[][2] = {{0, 0}};
    printf("%d\n", peopleOnBus(stops5, 1));
    return 0;
}