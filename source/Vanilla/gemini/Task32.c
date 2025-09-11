#include <stdio.h>

int calculateYears(double principal, double interest, double tax, double desired) {
    int years = 0;
    while (principal < desired) {
        principal += principal * interest * (1 - tax);
        years++;
    }
    return years;
}

int main() {
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1100.0)); // 3
    printf("%d\n", calculateYears(1000.0, 0.01625, 0.18, 1200.0)); // 14
    printf("%d\n", calculateYears(1000.0, 0.05, 0.18, 1000.0)); // 0
    printf("%d\n", calculateYears(1500.0, 0.045, 0.18, 2000.0)); // 8
    printf("%d\n", calculateYears(1000.0, 0.07, 0.0, 1140.0)); // 2
    return 0;
}