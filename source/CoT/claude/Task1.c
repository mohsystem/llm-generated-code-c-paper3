
#include <stdio.h>
#include <stdlib.h>

int countPassengers(int stops[][2], int size) {
    if (stops == NULL || size <= 0) {
        return -1;  // Error case
    }
    
    int total = 0;
    for(int i = 0; i < size; i++) {
        if(stops[i][0] < 0 || stops[i][1] < 0) {
            return -1;  // Error case: negative passengers
        }
        total += stops[i][0] - stops[i][1];
        if(total < 0) {
            return -1;  // Error case: negative total
        }
    }
    return total;
}

int main() {
    // Test cases
    int test1[][2] = {{10,0}, {3,5}, {2,5}};
    int test2[][2] = {{3,0}, {4,2}, {5,5}};
    int test3[][2] = {{20,0}, {10,5}, {5,15}};
    int test4[][2] = {{5,0}, {0,3}, {2,4}};
    int test5[][2] = {{15,0}, {5,5}, {5,8}};
    
    printf("Test 1: %d\\n", countPassengers(test1, 3)); // Expected: 5
    printf("Test 2: %d\\n", countPassengers(test2, 3)); // Expected: 5
    printf("Test 3: %d\\n", countPassengers(test3, 3)); // Expected: 15
    printf("Test 4: %d\\n", countPassengers(test4, 3)); // Expected: 0
    printf("Test 5: %d\\n", countPassengers(test5, 3)); // Expected: 12
    
    return 0;
}
