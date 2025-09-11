#include <stdio.h>

int calculateYears(double principal, double interest, double tax, double desired) {
    if (principal >= desired) return 0;
    int years = 0;
    while (principal < desired) {
        double accruedInterest = principal * interest;
        double taxedInterest = accruedInterest * (1 - tax);
        principal += taxedInterest;
        years++;
    }
    return years;
}

int main() {
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1100.00)); // 3
    printf("%d\n", calculateYears(1200.00, 0.04, 0.15, 1500.00)); // 8
    printf("%d\n", calculateYears(1500.00, 0.03, 0.20, 1500.00)); // 0
    printf("%d\n", calculateYears(2000.00, 0.05, 0.10, 2500.00)); // 6
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1000.00)); // 0
    return 0;
}