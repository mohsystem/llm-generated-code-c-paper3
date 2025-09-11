
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isNarcissistic(int number) {
    if (number <= 0) return false;
    
    // Count digits
    int temp = number;
    int len = 0;
    while (temp > 0) {
        len++;
        temp /= 10;
    }
    
    // Calculate sum
    temp = number;
    int sum = 0;
    while (temp > 0) {
        int digit = temp % 10;
        sum += pow(digit, len);
        temp /= 10;
    }
    
    return sum == number;
}

int main() {
    // Test cases
    printf("%d\\n", isNarcissistic(153));  // 1
    printf("%d\\n", isNarcissistic(1652)); // 0
    printf("%d\\n", isNarcissistic(370));  // 1
    printf("%d\\n", isNarcissistic(407));  // 1
    printf("%d\\n", isNarcissistic(1634)); // 1
    return 0;
}
