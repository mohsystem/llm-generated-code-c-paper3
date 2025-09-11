#include <stdio.h>

int peopleOnBus(int busStops[][2], int size) {
    int peopleOnBus = 0;
    for (int i = 0; i < size; i++) {
        peopleOnBus += busStops[i][0]; // People getting on
        peopleOnBus -= busStops[i][1]; // People getting off
    }
    return peopleOnBus;
}

int main() {
    int busStops1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    int busStops2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    int busStops3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    int busStops4[][2] = {{0, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    int busStops5[][2] = {{10, 0}, {3, 1}, {5, 8}, {7, 3}, {2, 4}, {8, 2}};
    
    printf("%d\n", peopleOnBus(busStops1, 3)); // 5
    printf("%d\n", peopleOnBus(busStops2, 6)); // 17
    printf("%d\n", peopleOnBus(busStops3, 6)); // 21
    printf("%d\n", peopleOnBus(busStops4, 6)); // 14
    printf("%d\n", peopleOnBus(busStops5, 6)); // 17
    
    return 0;
}