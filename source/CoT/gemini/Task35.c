#include <stdio.h>

int people_on_bus(int stops[][2], int num_stops) {
    int people = 0;
    for (int i = 0; i < num_stops; i++) {
        people += stops[i][0];
        people -= stops[i][1];
    }
    return people;
}

int main() {
    int stops1[][2] = {{10, 0}, {3, 5}, {2, 4}};
    printf("%d\n", people_on_bus(stops1, 3)); // Output: 4

    int stops2[][2] = {{5, 0}, {7, 2}, {1, 9}};
    printf("%d\n", people_on_bus(stops2, 3)); // Output: 1

    int stops3[][2] = {{0, 0}};
    printf("%d\n", people_on_bus(stops3, 1)); // Output: 0

    int stops4[][2] = {{10, 5}, {3, 8}};
    printf("%d\n", people_on_bus(stops4, 2)); // Output: 0

    int stops5[][2] = {{5, 0}, {2, 2}, {3, 1}};
    printf("%d\n", people_on_bus(stops5, 3)); // Output: 5

    return 0;
}