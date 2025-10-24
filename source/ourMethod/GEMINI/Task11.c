#include <stdio.h>
#include <math.h>

/**
 * @brief Calculates the number of years required for a population to reach a target.
 *
 * @param p0 Initial population. Must be > 0.
 * @param percent Annual percentage growth. Must be >= 0.
 * @param aug Annual net change in inhabitants (can be positive or negative).
 * @param p Target population. Must be > 0.
 * @return The number of full years to reach or exceed the target population.
 */
int nb_year(int p0, double percent, int aug, int p) {
    int years = 0;
    double current_population = (double)p0;
    double percent_decimal = percent / 100.0;
    
    while (current_population < p) {
        current_population = floor(current_population * (1.0 + percent_decimal) + aug);
        years++;
    }
    return years;
}

int main() {
    // Test Case 1: Standard growth
    printf("Test Case 1: Expected 15, Got %d\n", nb_year(1500, 5, 100, 5000));

    // Test Case 2: Large numbers
    printf("Test Case 2: Expected 10, Got %d\n", nb_year(1500000, 2.5, 10000, 2000000));

    // Test Case 3: Example from prompt
    printf("Test Case 3: Expected 3, Got %d\n", nb_year(1000, 2, 50, 1200));

    // Test Case 4: Initial population already meets target
    printf("Test Case 4: Expected 0, Got %d\n", nb_year(1200, 2, 50, 1200));

    // Test Case 5: Slow growth
    printf("Test Case 5: Expected 4, Got %d\n", nb_year(1000, 0.5, 20, 1100));

    return 0;
}