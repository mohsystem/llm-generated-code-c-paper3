#include <stdio.h>

int countPeople(int busStops[][2], int size) {
    int peopleOnBus = 0;
    for (int i = 0; i < size; i++) {
        peopleOnBus += busStops[i][0] - busStops[i][1];
    }
    return peopleOnBus;
}

int main() {
    int testCases[][5][2] = {
        {{10, 0}, {3, 5}, {5, 8}},
        {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}},
        {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}},
        {{0, 0}},
        {{10, 0}, {0, 5}, {2, 8}}
    };

    int sizes[] = {3, 6, 6, 1, 3};

    for (int i = 0; i < 5; i++) {
        printf("%d\n", countPeople(testCases[i], sizes[i]));
    }

    return 0;
}