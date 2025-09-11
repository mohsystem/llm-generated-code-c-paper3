
#include <stdio.h>

int countPassengers(int stops[][2], int size) {
    int passengers = 0;
    for(int i = 0; i < size; i++) {
        passengers += stops[i][0] - stops[i][1];
    }
    return passengers;
}

int main() {
    // Test cases
    int test1[][2] = {{10,0}, {3,5}, {5,8}};
    int test2[][2] = {{3,0}, {4,2}, {5,5}};
    int test3[][2] = {{20,0}, {10,5}, {5,15}};
    int test4[][2] = {{5,0}, {7,3}, {2,5}};
    int test5[][2] = {{15,0}, {10,5}, {5,8}, {3,12}};
    
    printf("%d\\n", countPassengers(test1, 3)); // Expected: 5
    printf("%d\\n", countPassengers(test2, 3)); // Expected: 5
    printf("%d\\n", countPassengers(test3, 3)); // Expected: 15
    printf("%d\\n", countPassengers(test4, 3)); // Expected: 6
    printf("%d\\n", countPassengers(test5, 4)); // Expected: 8
    
    return 0;
}
