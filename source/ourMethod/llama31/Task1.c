#include <stdio.h>
#include <stdlib.h>

int countPeopleOnBus(int stops[][2], int numStops) {
    int peopleOnBus = 0;
    for (int i = 0; i < numStops; i++) {
        peopleOnBus += stops[i][0] - stops[i][1];
        if (peopleOnBus < 0) {
            fprintf(stderr, "Number of people on the bus cannot be negative.\n");
            exit(EXIT_FAILURE);
        }
    }
    return peopleOnBus;
}

int main() {
    int testCase1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    printf("%d\n", countPeopleOnBus(testCase1, 3)); // Example test case

    int testCase2[][2] = {{10, 0}, {3, 5}, {5, 8}, {2, 2}};
    printf("%d\n", countPeopleOnBus(testCase2, 4)); // Another example test case

    return 0;
}