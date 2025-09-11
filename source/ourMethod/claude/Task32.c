
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

int calculate_years(double principal, double interest, double tax, double desired) {
    if (principal < 0 || interest < 0 || tax < 0 || desired < 0) {
        fprintf(stderr, "Error: Parameters cannot be negative\\n");
        return -1;
    }
    if (principal > desired) {
        fprintf(stderr, "Error: Principal cannot be greater than desired amount\\n");
        return -1;
    }
    if (principal == desired) {
        return 0;
    }
    
    int years = 0;
    double current_amount = principal;
    
    while (current_amount < desired) {
        double interest_earned = current_amount * interest;
        double tax_paid = interest_earned * tax;
        current_amount += (interest_earned - tax_paid);
        years++;
        
        if (years == INT_MAX) {
            fprintf(stderr, "Error: Years calculation overflow\\n");
            return -1;
        }
    }
    return years;
}

int main() {
    // Test cases
    printf("%d\\n", calculate_years(1000.00, 0.05, 0.18, 1100.00));  // Expected: 3
    printf("%d\\n", calculate_years(1000.00, 0.01625, 0.18, 1200.00));  // Expected: 14
    printf("%d\\n", calculate_years(1000.00, 0.05, 0.18, 1000.00));  // Expected: 0
    printf("%d\\n", calculate_years(100.00, 0.1, 0.1, 110.00));  // Expected: 2
    printf("%d\\n", calculate_years(1000.00, 0.05, 0.14, 1100.00));  // Expected: 3
    
    return 0;
}
