#include <stdio.h>

int peopleOnBus(int stops[][2], int numStops) {
    int people = 0;
    for (int i = 0; i < numStops; i++) {
        people += stops[i][0] - stops[i][1];
    }
    return people;
}

int main() {
    int test1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    printf("%d\n", peopleOnBus(test1, 3)); // 2

    int test2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    printf("%d\n", peopleOnBus(test2, 6)); // 17

    int test3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    printf("%d\n", peopleOnBus(test3, 6)); // 21

    int test4[][2] = {{0, 0}};
    printf("%d\n", peopleOnBus(test4, 1)); // 0

    int test5[][2] = {{10, 3}, {5, 2}, {7, 5}, {1, 1}};
    printf("%d\n", peopleOnBus(test5, 4)); // 8

    return 0;
}