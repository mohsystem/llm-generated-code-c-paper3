#include <stdio.h>

int peopleOnTheBus(int busStops[][2], int n) {
    int peopleOnBus = 0;
    for (int i = 0; i < n; i++) {
        peopleOnBus += busStops[i][0];
        peopleOnBus -= busStops[i][1];
    }
    return peopleOnBus;
}

int main() {
    int test1[][2] = {{10, 0}, {3, 5}, {2, 5}};
    int test2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    int test3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    int test4[][2] = {{0, 0}};
    int test5[][2] = {{5, 0}, {2, 2}, {3, 4}};

    printf("%d\n", peopleOnTheBus(test1, 3)); // 5
    printf("%d\n", peopleOnTheBus(test2, 6)); // 17
    printf("%d\n", peopleOnTheBus(test3, 6)); // 21
    printf("%d\n", peopleOnTheBus(test4, 1)); // 0
    printf("%d\n", peopleOnTheBus(test5, 3)); // 4

    return 0;
}