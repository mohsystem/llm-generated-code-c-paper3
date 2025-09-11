#include <stdio.h>

int peopleOnBus(int stops[][2], int numStops) {
    int people = 0;
    for (int i = 0; i < numStops; i++) {
        people += stops[i][0];
        people -= stops[i][1];
    }
    return people;
}

int main() {
    int test1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    int test2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    int test3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    int test4[][2] = {};
    int test5[][2] = {{0,0}};


    printf("Test 1: %d\n", peopleOnBus(test1, 3)); // Expected 5
    printf("Test 2: %d\n", peopleOnBus(test2, 6)); // Expected 17
    printf("Test 3: %d\n", peopleOnBus(test3, 6)); // Expected 21
    printf("Test 4: %d\n", peopleOnBus(test4, 0)); // Expected 0
    printf("Test 5: %d\n", peopleOnBus(test5, 1)); // Expected 0


    return 0;
}