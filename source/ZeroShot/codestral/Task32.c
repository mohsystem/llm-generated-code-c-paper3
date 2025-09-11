#include<stdio.h>

int calculateYears(double principal, double interest, double tax, double desired) {
    int years = 0;
    while (principal < desired) {
        double interestEarned = principal * interest;
        double taxAmount = interestEarned * tax;
        principal += interestEarned - taxAmount;
        years++;
    }
    return years;
}

int main() {
    printf("%d\n", calculateYears(1000.00, 0.05, 0.18, 1100.00)); // 3
    return 0;
}