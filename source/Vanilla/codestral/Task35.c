#include <stdio.h>

int number(int busStops[5][2], int size) {
    int totalPeople = 0;
    for (int i = 0; i < size; i++) {
        totalPeople += busStops[i][0] - busStops[i][1];
    }
    return totalPeople;
}

int main() {
    int busStops1[3][2] = {{10,0},{3,5},{5,8}};
    printf("%d\n", number(busStops1, 3)); // Output: 5

    int busStops2[6][2] = {{3,0},{9,1},{4,10},{12,2},{6,1},{7,10}};
    printf("%d\n", number(busStops2, 6)); // Output: 17

    int busStops3[6][2] = {{3,0},{9,1},{4,8},{12,2},{6,1},{7,8}};
    printf("%d\n", number(busStops3, 6)); // Output: 21

    int busStops4[1][2] = {{0,0}};
    printf("%d\n", number(busStops4, 1)); // Output: 0

    int busStops5[2][2] = {{10,10},{10,10}};
    printf("%d\n", number(busStops5, 2)); // Output: 0

    return 0;
}