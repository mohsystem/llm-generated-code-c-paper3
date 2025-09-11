#include <stdio.h>
#include <math.h>

int isNarcissistic(int number) {
    int numDigits = 0, temp = number, sum = 0;
    
    while (temp > 0) {
        numDigits++;
        temp /= 10;
    }
    
    temp = number;
    while (temp > 0) {
        int digit = temp % 10;
        sum += pow(digit, numDigits);
        temp /= 10;
    }
    
    return sum == number;
}

int main() {
    printf("%d\n", isNarcissistic(153));  // 1 (true)
    printf("%d\n", isNarcissistic(1652)); // 0 (false)
    printf("%d\n", isNarcissistic(9474)); // 1 (true)
    printf("%d\n", isNarcissistic(9475)); // 0 (false)
    printf("%d\n", isNarcissistic(407));  // 1 (true)
    return 0;
}