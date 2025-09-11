#include <stdio.h>

int number_of_people_on_bus(int people[][2], int size) {
    int peopleOnBus = 0;
    for (int i = 0; i < size; i++) {
        peopleOnBus += people[i][0] - people[i][1];
    }
    return peopleOnBus;
}

int main() {
    int testCases[][2] = {{10, 0}, {3, 5}, {5, 8}};
    printf("%d\n", number_of_people_on_bus(testCases, 3));  // Output: 5

    int testCases2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    printf("%d\n", number_of_people_on_bus(testCases2, 6));  // Output: 17

    int testCases3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    printf("%d\n", number_of_people_on_bus(testCases3, 6));  // Output: 21

    int testCases4[][2] = {{0, 0}};
    printf("%d\n", number_of_people_on_bus(testCases4, 1));  // Output: 0

    int testCases5[][2] = {{0, 0}, {0, 0}};
    printf("%d\n", number_of_people_on_bus(testCases5, 2));  // Output: 0

    return 0;
}