#include <stdio.h>

int peopleOnBus(int busStops[][2], int length) {
    int totalPeople = 0;
    for (int i = 0; i < length; i++) {
        totalPeople += busStops[i][0] - busStops[i][1];
    }
    return totalPeople;
}

int main() {
    int stops1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    int stops2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    int stops3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    int stops4[][2] = {{0, 0}};
    int stops5[][2] = {{10, 0}, {3, 5}, {2, 2}};
    
    printf("%d\n", peopleOnBus(stops1, 3)); // 5
    printf("%d\n", peopleOnBus(stops2, 6)); // 17
    printf("%d\n", peopleOnBus(stops3, 6)); // 21
    printf("%d\n", peopleOnBus(stops4, 1)); // 0
    printf("%d\n", peopleOnBus(stops5, 3)); // 8

    return 0;
}