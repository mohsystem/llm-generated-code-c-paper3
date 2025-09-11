#include <stdio.h>

int numberOfPeopleOnBus(int stops[][2], int n) {
    int peopleOnBus = 0;
    for (int i = 0; i < n; i++) {
        peopleOnBus += stops[i][0];
        peopleOnBus -= stops[i][1];
    }
    return peopleOnBus;
}

int main() {
    int stops1[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    int stops2[][2] = {{10, 0}, {3, 5}, {5, 8}};
    int stops3[][2] = {{3, 0}, {2, 1}, {5, 5}, {8, 2}, {6, 4}};
    int stops4[][2] = {{0, 0}, {2, 1}, {5, 3}, {3, 2}};
    int stops5[][2] = {{5, 0}, {0, 0}, {0, 0}, {2, 1}};
    printf("%d\n", numberOfPeopleOnBus(stops1, 6)); // 5
    printf("%d\n", numberOfPeopleOnBus(stops2, 3)); // 5
    printf("%d\n", numberOfPeopleOnBus(stops3, 5)); // 12
    printf("%d\n", numberOfPeopleOnBus(stops4, 4)); // 4
    printf("%d\n", numberOfPeopleOnBus(stops5, 4)); // 6
    return 0;
}