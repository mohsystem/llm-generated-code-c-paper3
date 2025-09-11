
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

bool isNarcissistic(int number) {
    if (number <= 0) {
        return false;
    }
    
    char numStr[12]; // Enough for max int
    sprintf(numStr, "%d", number);
    int power = strlen(numStr);
    long long sum = 0; // Using long long to prevent overflow
    
    for (int i = 0; numStr[i] != '\\0'; i++) {
        int digit = numStr[i] - '0';
        sum += (long long)pow(digit, power);
        if (sum > INT_MAX) { // Prevent overflow
            return false;
        }
    }
    
    return sum == number;
}

int main() {
    // Test cases
    printf("%d\\n", isNarcissistic(153));  // 1
    printf("%d\\n", isNarcissistic(1652)); // 0
    printf("%d\\n", isNarcissistic(7));    // 1
    printf("%d\\n", isNarcissistic(370));  // 1
    printf("%d\\n", isNarcissistic(1000)); // 0
    return 0;
}
