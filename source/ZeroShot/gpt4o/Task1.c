#include <stdio.h>

int numberOfPeopleOnBus(int busStops[][2], int size) {
    int peopleOnBus = 0;
    for (int i = 0; i < size; ++i) {
        peopleOnBus += busStops[i][0];
        peopleOnBus -= busStops[i][1];
    }
    return peopleOnBus;
}

int main() {
    int busStops1[][2] = {{10, 0}, {3, 5}, {5, 8}, {2, 1}, {8, 10}};
    printf("%d\n", numberOfPeopleOnBus(busStops1, 5)); // 4

    int busStops2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    printf("%d\n", numberOfPeopleOnBus(busStops2, 6)); // 17

    int busStops3[][2] = {{5, 0}, {2, 2}, {3, 3}, {1, 5}, {0, 0}};
    printf("%d\n", numberOfPeopleOnBus(busStops3, 5)); // 1

    int busStops4[][2] = {{0, 0}, {4, 1}, {8, 2}, {4, 3}, {2, 4}};
    printf("%d\n", numberOfPeopleOnBus(busStops4, 5)); // 8

    int busStops5[][2] = {{7, 0}, {3, 3}, {8, 5}, {1, 1}, {4, 6}};
    printf("%d\n", numberOfPeopleOnBus(busStops5, 5)); // 8

    return 0;
}