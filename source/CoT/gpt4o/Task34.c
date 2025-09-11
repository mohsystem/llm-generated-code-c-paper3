#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool isNarcissistic(int number) {
    int originalNumber = number;
    int sum = 0;
    int numDigits = 0;
    int temp = number;

    while (temp > 0) {
        numDigits++;
        temp /= 10;
    }

    temp = number;
    while (temp > 0) {
        int digit = temp % 10;
        sum += (int)pow(digit, numDigits);
        temp /= 10;
    }

    return sum == originalNumber;
}

int main() {
    printf("%d\n", isNarcissistic(153));  // 1 (true)
    printf("%d\n", isNarcissistic(1652)); // 0 (false)
    printf("%d\n", isNarcissistic(9474)); // 1 (true)
    printf("%d\n", isNarcissistic(9475)); // 0 (false)
    printf("%d\n", isNarcissistic(407));  // 1 (true)

    return 0;
}