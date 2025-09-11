
#include <stdio.h>
#include <stdlib.h>

int countPassengers(int stops[][2], int stopsCount) {
    if (stops == NULL || stopsCount < 0) {
        return -1;  // Error case
    }
    
    if (stopsCount == 0) {
        return 0;
    }
    
    int passengers = 0;
    
    for (int i = 0; i < stopsCount; i++) {
        int getting_on = stops[i][0];
        int getting_off = stops[i][1];
        
        if (getting_on < 0 || getting_off < 0) {
            return -1;  // Error case: negative passengers
        }
        
        if (i == 0 && getting_off != 0) {
            return -1;  // Error case: first stop must have 0 getting off
        }
        
        passengers += getting_on - getting_off;
        
        if (passengers < 0) {
            return -1;  // Error case: negative total
        }
    }
    
    return passengers;
}

int main() {
    // Test cases
    int test1[][2] = {{10,0}, {3,5}, {5,8}};
    int test2[][2] = {{3,0}, {4,2}, {5,5}};
    int test3[][2] = {{20,0}, {10,5}, {5,5}};
    int test4[][2] = {{5,0}};
    int test5[][2] = {{3,0}, {4,4}, {5,6}};
    
    printf("Test 1: %d\\n", countPassengers(test1, 3));  // Expected: 5
    printf("Test 2: %d\\n", countPassengers(test2, 3));  // Expected: 5
    printf("Test 3: %d\\n", countPassengers(test3, 3));  // Expected: 25
    printf("Test 4: %d\\n", countPassengers(test4, 1));  // Expected: 5
    printf("Test 5: %d\\n", countPassengers(test5, 3));  // Expected: 2
    
    return 0;
}
