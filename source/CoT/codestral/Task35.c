#include <stdio.h>

int numberOfPeople(int stops[][2], int size) {
    int peopleInBus = 0;
    for (int i = 0; i < size; i++) {
        peopleInBus += stops[i][0] - stops[i][1];
    }
    return peopleInBus;
}

int main() {
    int testCases[][5][2] = {
        {{10, 0}, {3, 5}, {2, 5}},
        {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}},
        {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}},
        {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}},
        {{0, 0}}
    };
    int sizes[] = {3, 6, 6, 6, 1};
    for (int i = 0; i < 5; i++) {
        printf("%d\n", numberOfPeople(testCases[i], sizes[i]));
    }
    return 0;
}