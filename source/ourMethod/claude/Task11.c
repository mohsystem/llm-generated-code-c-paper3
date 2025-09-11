
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int nb_year(int p0, double percent, int aug, int p) {
    if (p0 <= 0 || percent < 0 || p <= 0) {
        fprintf(stderr, "Invalid input parameters\\n");
        return -1;
    }
    
    int years = 0;
    long long current_population = p0;
    double percent_decimal = percent / 100.0;
    
    while (current_population < p) {
        current_population = (long long)(current_population + 
                                      (current_population * percent_decimal) + aug);
        years++;
        
        // Check for potential overflow
        if (current_population > INT_MAX) {
            fprintf(stderr, "Population exceeded maximum value\\n");
            return -1;
        }
    }
    return years;
}

int main() {
    // Test cases
    printf("%d\\n", nb_year(1000, 2, 50, 1200));  // Expected: 3
    printf("%d\\n", nb_year(1500, 5, 100, 5000));  // Expected: 15
    printf("%d\\n", nb_year(1500000, 2.5, 10000, 2000000));  // Expected: 10
    printf("%d\\n", nb_year(1600, 2, 50, 2000));  // Expected: 13
    printf("%d\\n", nb_year(1000, 2.0, 50, 1214));  // Expected: 4
    
    return 0;
}
