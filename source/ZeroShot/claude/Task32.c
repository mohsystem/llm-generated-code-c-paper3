
#include <stdio.h>

int calculateYears(double principal, double interest, double tax, double desired) {
    if(principal >= desired) return 0;
    
    int years = 0;
    double currentAmount = principal;
    
    while(currentAmount < desired) {
        double interestEarned = currentAmount * interest;
        double taxPaid = interestEarned * tax;
        currentAmount += interestEarned - taxPaid;
        years++;
    }
    
    return years;
}

int main() {
    printf("%d\\n", calculateYears(1000.00, 0.05, 0.18, 1100.00));  // 3
    printf("%d\\n", calculateYears(1000.00, 0.01625, 0.18, 1200.00));  // 14
    printf("%d\\n", calculateYears(1000.00, 0.05, 0.18, 1000.00));  // 0
    printf("%d\\n", calculateYears(100.00, 0.1, 0.1, 110.00));  // 1
    printf("%d\\n", calculateYears(500.00, 0.07, 0.15, 800.00));  // 7
    return 0;
}
