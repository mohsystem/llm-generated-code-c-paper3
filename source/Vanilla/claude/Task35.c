
#include <stdio.h>

int countPassengers(int stops[][2], int length) {
    int total = 0;
    for(int i = 0; i < length; i++) {
        total += stops[i][0] - stops[i][1];
    }
    return total;
}

int main() {
    // Test cases
    int test1[][2] = {{10,0}, {3,5}, {2,5}};
    int test2[][2] = {{3,0}, {4,2}, {5,5}};
    int test3[][2] = {{20,0}, {10,5}, {5,15}};
    int test4[][2] = {{5,0}, {7,3}, {2,4}, {9,2}};
    int test5[][2] = {{2,0}, {3,1}, {4,2}, {5,3}, {1,4}};
    
    printf("%d\\n", countPassengers(test1, 3)); // Expected: 5
    printf("%d\\n", countPassengers(test2, 3)); // Expected: 5
    printf("%d\\n", countPassengers(test3, 3)); // Expected: 15
    printf("%d\\n", countPassengers(test4, 4)); // Expected: 14
    printf("%d\\n", countPassengers(test5, 5)); // Expected: 5
    
    return 0;
}
