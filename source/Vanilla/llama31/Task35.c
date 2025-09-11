#include <stdio.h>

int countPeopleOnBus(int stops[][2], int size) {
    int peopleOnBus = 0;
    for (int i = 0; i < size; i++) {
        peopleOnBus += stops[i][0] - stops[i][1];
    }
    return peopleOnBus;
}

int main() {
    int testCases[][2] = {
        {10, 0}, {3, 5}, {5, 8}
    };
    printf("%d\n", countPeopleOnBus(testCases, 3)); // Output: 5

    int testCases2[][2] = {
        {3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}
    };
    printf("%d\n", countPeopleOnBus(testCases2, 6)); // Output: 9

    int testCases3[][2] = {
        {3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}
    };
    printf("%d\n", countPeopleOnBus(testCases3, 6)); // Output: 7

    int testCases4[][2] = {
        {0, 0}
    };
    printf("%d\n", countPeopleOnBus(testCases4, 1)); // Output: 0

    int testCases5[][2] = {
        {10, 0}, {0, 5}, {5, 8}
    };
    printf("%d\n", countPeopleOnBus(testCases5, 3)); // Output: 2

    return 0;
}