
int calculateYears(double principal, double interest, double tax, double desired) {
    if (principal >= desired) return 0;
    
    int years = 0;
    double current = principal;
    
    while (current < desired) {
        double interestEarned = current * interest;
        double taxPaid = interestEarned * tax;
        current += interestEarned - taxPaid;
        years++;
    }
    
    return years;
}

#include <stdio.h>

int main() {
    printf("%d\\n", calculateYears(1000.00, 0.05, 0.18, 1100.00));  // 3
    printf("%d\\n", calculateYears(1000.00, 0.01625, 0.18, 1200.00));  // 14
    printf("%d\\n", calculateYears(1000.00, 0.05, 0.18, 1000.00));  // 0
    printf("%d\\n", calculateYears(100.00, 0.1, 0.1, 110.00));  // 1
    printf("%d\\n", calculateYears(1000.00, 0.05, 0.14, 1500.00));  // 6
    return 0;
}
