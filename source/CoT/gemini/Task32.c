#include <stdio.h>

int calculateYears(double principal, double interest, double tax, double desired) {
    int years = 0;
    while (principal < desired) {
        double yearlyInterest = principal * interest;
        double taxAmount = yearlyInterest * tax;
        principal += yearlyInterest - taxAmount;
        years++;
    }
    return years;
}

int main() {
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1100.0)); // 3
    printf("%d\n", calculateYears(1000.0, 0.01625, 0.05, 1200.0)); // 14
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1000.0)); // 0
    printf("%d\n", calculateYears(1500.0, 0.045, 0.18, 2000.0)); // 8
    printf("%d\n", calculateYears(500.0, 0.07, 0.10, 1000.0)); // 11
    return 0;
}