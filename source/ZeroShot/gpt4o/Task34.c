#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isNarcissistic(int number) {
    int originalNumber = number;
    int sum = 0;
    int numDigits = 0;
    int temp = number;
    
    while (temp > 0) {
        temp /= 10;
        numDigits++;
    }
    
    temp = number;
    while (temp > 0) {
        int digit = temp % 10;
        sum += pow(digit, numDigits);
        temp /= 10;
    }
    
    return sum == originalNumber;
}

int main() {
    printf("%s\n", isNarcissistic(153) ? "true" : "false");  // true
    printf("%s\n", isNarcissistic(1652) ? "true" : "false"); // false
    printf("%s\n", isNarcissistic(9474) ? "true" : "false"); // true
    printf("%s\n", isNarcissistic(9475) ? "true" : "false"); // false
    printf("%s\n", isNarcissistic(370) ? "true" : "false");  // true
    return 0;
}