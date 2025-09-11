#include <stdio.h>

int calculateYears(double principal, double interest, double tax, double desired) {
    int years = 0;
    while (principal < desired) {
        double interestEarned = principal * interest;
        double taxPaid = interestEarned * tax;
        principal += interestEarned - taxPaid;
        years++;
    }
    return years;
}

int main() {
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1100.00)); // 3
    printf("%d\n", calculateYears(1000.00, 0.01625, 0.18, 1200.00)); // 14
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1000.00)); // 0
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1110.00)); // 4
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1150.00)); // 5
    return 0;
}