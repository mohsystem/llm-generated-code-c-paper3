#include <stdio.h>

int countPeople(int busStops[][2], int size) {
    int peopleOnBus = 0;
    for (int i = 0; i < size; i++) {
        peopleOnBus += busStops[i][0] - busStops[i][1];
    }
    return peopleOnBus;
}

int main() {
    int testCase1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    printf("%d\n", countPeople(testCase1, 3));  // Expected output: 5

    int testCase2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    printf("%d\n", countPeople(testCase2, 6));  // Expected output: 17

    int testCase3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    printf("%d\n", countPeople(testCase3, 6));  // Expected output: 21

    return 0;
}