#include <stdio.h>

/**
 * @brief Calculates the number of people still on the bus after the last bus stop.
 * 
 * @param stops A 2D array of integer pairs. Each pair represents [people get on, people get off].
 * @param num_stops The number of stops (rows) in the array.
 * @return The number of people left on the bus.
 */
int countPassengers(const int stops[][2], int num_stops) {
    int peopleOnBus = 0;
    for (int i = 0; i < num_stops; i++) {
        peopleOnBus += stops[i][0];
        peopleOnBus -= stops[i][1];
    }
    return peopleOnBus;
}

void run_test_case(const char* name, const int stops[][2], int num_stops) {
    printf("%s: {", name);
    for (int i = 0; i < num_stops; ++i) {
        printf("{%d,%d}", stops[i][0], stops[i][1]);
        if (i < num_stops - 1) printf(", ");
    }
    printf("}\n");
    printf("Remaining passengers: %d\n", countPassengers(stops, num_stops));
}


int main() {
    // Test Case 1
    const int stops1[][2] = {{10, 0}, {3, 5}, {5, 8}};
    int num_stops1 = sizeof(stops1) / sizeof(stops1[0]);
    run_test_case("Test Case 1", stops1, num_stops1); // Expected: 5

    printf("\n");
    // Test Case 2
    const int stops2[][2] = {{3, 0}, {9, 1}, {4, 10}, {12, 2}, {6, 1}, {7, 10}};
    int num_stops2 = sizeof(stops2) / sizeof(stops2[0]);
    run_test_case("Test Case 2", stops2, num_stops2); // Expected: 17

    printf("\n");
    // Test Case 3
    const int stops3[][2] = {{3, 0}, {9, 1}, {4, 8}, {12, 2}, {6, 1}, {7, 8}};
    int num_stops3 = sizeof(stops3) / sizeof(stops3[0]);
    run_test_case("Test Case 3", stops3, num_stops3); // Expected: 21

    printf("\n");
    // Test Case 4
    const int stops4[][2] = {{0, 0}};
    int num_stops4 = sizeof(stops4) / sizeof(stops4[0]);
    run_test_case("Test Case 4", stops4, num_stops4); // Expected: 0

    printf("\n");
    // Test Case 5
    const int stops5[][2] = {{100, 0}, {0, 50}, {20, 30}};
    int num_stops5 = sizeof(stops5) / sizeof(stops5[0]);
    run_test_case("Test Case 5", stops5, num_stops5); // Expected: 40

    return 0;
}