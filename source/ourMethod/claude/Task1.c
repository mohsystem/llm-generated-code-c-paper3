
#include <stdio.h>
#include <stdlib.h>

struct BusStop {
    int on;
    int off;
};

int countPassengers(const struct BusStop* stops, size_t length) {
    if (stops == NULL || length == 0) {
        return 0;
    }
    
    int passengers = 0;
    for (size_t i = 0; i < length; i++) {
        // Validate input
        if (stops[i].on < 0 || stops[i].off < 0) {
            return 0;
        }
        
        // Check for integer overflow
        if (passengers > INT_MAX - stops[i].on) {
            return 0;
        }
        passengers += stops[i].on;
        
        // Check for negative passengers
        if (passengers < stops[i].off) {
            return 0;
        }
        passengers -= stops[i].off;
    }
    return passengers;
}

int main() {
    // Test cases
    struct BusStop test1[] = {{10,0}, {3,5}, {5,8}};
    struct BusStop test2[] = {{3,0}};
    struct BusStop test3[] = {{20,0}, {10,5}, {5,15}};
    struct BusStop test4[] = {{0,0}};
    struct BusStop test5[] = {{10,0}, {0,10}};
    
    printf("%d\\n", countPassengers(test1, 3));  // Expected: 5
    printf("%d\\n", countPassengers(test2, 1));  // Expected: 3
    printf("%d\\n", countPassengers(test3, 3));  // Expected: 15
    printf("%d\\n", countPassengers(test4, 1));  // Expected: 0
    printf("%d\\n", countPassengers(test5, 2));  // Expected: 0
    
    return 0;
}
