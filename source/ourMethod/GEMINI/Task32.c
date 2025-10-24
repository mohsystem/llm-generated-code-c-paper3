#include <stdio.h>

/**
 * @brief Calculates the number of years required for a principal to reach a desired sum.
 * 
 * @param principal The initial principal amount.
 * @param interest The annual interest rate (e.g., 0.05 for 5%).
 * @param tax The tax rate on the interest earned (e.g., 0.18 for 18%).
 * @param desired The desired final sum of money.
 * @return The number of years as a whole number.
 */
int calculateYears(double principal, double interest, double tax, double desired) {
    if (desired <= principal) {
        return 0;
    }

    int years = 0;
    double currentPrincipal = principal;

    // The problem's constraints assume the principal will always grow towards the desired sum.
    while (currentPrincipal < desired) {
        double interest_earned = currentPrincipal * interest;
        double tax_on_interest = interest_earned * tax;
        currentPrincipal += interest_earned - tax_on_interest;
        years++;
    }

    return years;
}

int main() {
    // Test Case 1: Example from prompt
    printf("Test Case 1 (P=1000, I=0.05, T=0.18, D=1100): %d\n", calculateYears(1000.0, 0.05, 0.18, 1100.0)); // Expected: 3

    // Test Case 2: Desired sum is already met
    printf("Test Case 2 (P=1000, I=0.05, T=0.18, D=1000): %d\n", calculateYears(1000.0, 0.05, 0.18, 1000.0)); // Expected: 0

    // Test Case 3: Longer term investment
    printf("Test Case 3 (P=100, I=0.02, T=0.1, D=120): %d\n", calculateYears(100.0, 0.02, 0.1, 120.0)); // Expected: 11

    // Test Case 4: High interest, low tax
    printf("Test Case 4 (P=5000, I=0.1, T=0.1, D=6000): %d\n", calculateYears(5000.0, 0.1, 0.1, 6000.0)); // Expected: 3
    
    // Test Case 5: Just crossing the threshold
    printf("Test Case 5 (P=2000, I=0.03, T=0.2, D=2100): %d\n", calculateYears(2000.0, 0.03, 0.2, 2100.0)); // Expected: 3

    return 0;
}