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
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1100.00)); // 3
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1200.00)); // 6
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1300.00)); // 9
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1500.00)); // 15
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1000.00)); // 0
    return 0;
}