#include <stdio.h>

int calculateYears(double principal, double interestRate, double taxRate, double desired) {
    int years = 0;
    while (principal < desired) {
        double interest = principal * interestRate;
        double afterTaxInterest = interest - (interest * taxRate);
        principal += afterTaxInterest;
        years++;
    }
    return years;
}

int main() {
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1100.0)); // 3
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1200.0)); // 6
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1000.0)); // 0
    printf("%d\n", calculateYears(1500.0, 0.03, 0.18, 2000.0)); // 16
    printf("%d\n", calculateYears(1000.0, 0.05, 0.0, 1100.0));  // 2
    return 0;
}