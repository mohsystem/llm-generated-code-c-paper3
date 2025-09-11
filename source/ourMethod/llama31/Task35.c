#include <stdio.h>
#include <stdlib.h>

int number_of_people_on_bus(int stops[][2], int size) {
    int peopleOnBus = 0;
    for (int i = 0; i < size; i++) {
        peopleOnBus += stops[i][0] - stops[i][1];
        // Ensure the number of people does not go below 0
        peopleOnBus = (peopleOnBus > 0) ? peopleOnBus : 0;
    }
    return peopleOnBus;
}

int main() {
    int testCases[][2] = {{10, 0}, {3, 5}, {5, 8}};
    printf("%d\n", number_of_people_on_bus(testCases, 3)); // Expected output: 0

    int testCases2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    printf("%d\n", number_of_people_on_bus(testCases2, 6)); // Expected output: 17

    int testCases3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    printf("%d\n", number_of_people_on_bus(testCases3, 6)); // Expected output: 21

    return 0;
}