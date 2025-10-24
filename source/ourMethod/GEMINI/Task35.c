#include <stdio.h>
#include <stddef.h> // For size_t

/**
 * @brief Calculates the number of people still on the bus after the last bus stop.
 * 
 * @param stops A 2D array where each inner array is a pair [people_on, people_off].
 * @param num_stops The number of stops (rows in the array).
 * @return The number of people remaining on the bus.
 */
int countPassengers(const int stops[][2], size_t num_stops) {
    int peopleOnBus = 0;
    for (size_t i = 0; i < num_stops; ++i) {
        peopleOnBus += stops[i][0];
        peopleOnBus -= stops[i][1];
    }
    return peopleOnBus;
}

int main() {
    // Test Case 1
    const int test1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    size_t size1 = sizeof(test1) / sizeof(test1[0]);
    printf("Test Case 1: %d\n", countPassengers(test1, size1)); // Expected: 5

    // Test Case 2
    const int test2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    size_t size2 = sizeof(test2) / sizeof(test2[0]);
    printf("Test Case 2: %d\n", countPassengers(test2, size2)); // Expected: 17

    // Test Case 3
    const int test3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    size_t size3 = sizeof(test3) / sizeof(test3[0]);
    printf("Test Case 3: %d\n", countPassengers(test3, size3)); // Expected: 21

    // Test Case 4
    const int test4[][2] = {{1, 0}};
    size_t size4 = sizeof(test4) / sizeof(test4[0]);
    printf("Test Case 4: %d\n", countPassengers(test4, size4)); // Expected: 1

    // Test Case 5 (Empty)
    const int (*test5)[2] = NULL;
    printf("Test Case 5 (Empty): %d\n", countPassengers(test5, 0)); // Expected: 0
    
    return 0;
}