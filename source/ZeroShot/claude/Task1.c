
#include <stdio.h>

int countPassengers(int stops[][2], int size) {
    int people = 0;
    for(int i = 0; i < size; i++) {
        people += stops[i][0] - stops[i][1];
    }
    return people;
}

int main() {
    // Test cases
    int test1[][2] = {{10,0}, {3,5}, {5,8}};                  // Expected: 5
    int test2[][2] = {{3,0}, {4,2}, {5,5}};                   // Expected: 5
    int test3[][2] = {{20,0}, {10,5}, {5,15}, {5,10}};       // Expected: 10
    int test4[][2] = {{5,0}, {0,3}, {2,4}};                   // Expected: 0
    int test5[][2] = {{15,0}, {10,5}, {7,8}};                 // Expected: 19
    
    printf("%d\\n", countPassengers(test1, 3));
    printf("%d\\n", countPassengers(test2, 3));
    printf("%d\\n", countPassengers(test3, 4));
    printf("%d\\n", countPassengers(test4, 3));
    printf("%d\\n", countPassengers(test5, 3));
    
    return 0;
}
