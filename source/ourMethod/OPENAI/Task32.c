#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdbool.h>

static bool is_finite(double x) {
    return isfinite(x) != 0;
}

// Computes the number of years needed to reach desired amount with yearly interest and tax on interest.
// Returns -1 for invalid inputs or if the target cannot be reached (e.g., non-positive growth when D > P).
long long years_to_target(double principal, double interest_rate, double tax_rate, double desired) {
    if (!is_finite(principal) || !is_finite(interest_rate) || !is_finite(tax_rate) || !is_finite(desired)) {
        return -1;
    }
    if (principal < 0.0 || desired < 0.0 || interest_rate < 0.0 || tax_rate < 0.0 || tax_rate > 1.0) {
        return -1;
    }
    if (desired <= principal) {
        return 0;
    }

    double effective_rate = interest_rate * (1.0 - tax_rate);
    if (effective_rate <= 0.0) {
        return -1; // Cannot reach a higher desired amount without positive growth
    }

    long long years = 0;
    double amount = principal;

    while (amount < desired) {
        double interest = amount * interest_rate;
        double net_gain = interest * (1.0 - tax_rate);
        amount += net_gain;
        years++;

        if (!is_finite(amount)) {
            return -1;
        }
    }

    return years;
}

static void run_test(double p, double i, double t, double d) {
    long long y = years_to_target(p, i, t, d);
    printf("P=%.2f I=%.4f T=%.4f D=%.2f => Years=%lld\n", p, i, t, d, y);
}

int main(void) {
    // 5 test cases
    run_test(1000.00, 0.05, 0.18, 1100.00); // Expected 3
    run_test(5000.00, 0.05, 0.20, 5000.00); // Expected 0
    run_test(1000.00, 0.05, 1.20, 1100.00); // Invalid tax, Expected -1
    run_test(1000.00, 0.00, 0.18, 1001.00); // Zero growth, Expected -1
    run_test(1500.00, 0.07, 0.25, 2000.00); // Expected 6
    return 0;
}