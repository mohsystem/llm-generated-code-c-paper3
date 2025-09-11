#include <stdio.h>
#include <math.h>

int isNarcissistic(int number) {
    int originalNumber = number;
    int sum = 0;
    int numberOfDigits = 0;
    int temp = number;
    
    while (temp > 0) {
        temp /= 10;
        numberOfDigits++;
    }
    
    temp = number;
    while (temp > 0) {
        int digit = temp % 10;
        sum += pow(digit, numberOfDigits);
        temp /= 10;
    }
    
    return sum == originalNumber;
}

int main() {
    printf("%d\n", isNarcissistic(153)); // true
    printf("%d\n", isNarcissistic(1652)); // false
    printf("%d\n", isNarcissistic(9474)); // true
    printf("%d\n", isNarcissistic(370)); // true
    printf("%d\n", isNarcissistic(7)); // true
    
    return 0;
}