#include <stdio.h>

int calculateYears(double principal, double interest, double tax, double desired) {
    if (desired <= principal) {
        return 0;
    }
    int years = 0;
    while (principal < desired) {
        double gain = principal * interest;
        double taxes = gain * tax;
        principal += gain - taxes;
        years++;
    }
    return years;
}

int main() {
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1100.00)); // Expected output: 3
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1000.00)); // Expected output: 0
    printf("%d\n", calculateYears(500.00, 0.10, 0.20, 600.00)); // Expected output: 2
    printf("%d\n", calculateYears(2000.00, 0.03, 0.15, 2500.00)); // Expected output: 10
    printf("%d\n", calculateYears(1500.00, 0.07, 0.12, 2000.00)); // Expected output: 6
    return 0;
}