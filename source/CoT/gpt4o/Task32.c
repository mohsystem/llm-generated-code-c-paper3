#include <stdio.h>

int calculateYears(double principal, double interest, double tax, double desired) {
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
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1100.0)); // 3
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1200.0)); // 6
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1500.0)); // 15
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1000.0)); // 0
    printf("%d\n", calculateYears(1000.0, 0.1, 0.18, 1100.0));  // 1
    return 0;
}