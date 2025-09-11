#include <stdio.h>

int countPeopleOnBus(int stops[][2], int n) {
    int peopleOnBus = 0;
    for (int i = 0; i < n; i++) {
        peopleOnBus += stops[i][0] - stops[i][1];
    }
    return peopleOnBus;
}

int main() {
    int testCases[][2][3] = {
        {{10, 0}, {3, 5}, {5, 8}},
        {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}},
        {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}},
        {{0, 0}},
        {{0, 0}, {0, 0}}
    };
    int testCaseSizes[] = {3, 6, 6, 1, 2};

    for (int i = 0; i < 5; i++) {
        printf("%d\n", countPeopleOnBus(testCases[i], testCaseSizes[i]));
    }

    return 0;
}