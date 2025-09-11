#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

bool isNarcissistic(int number) {
    char numStr[20]; // Adjust size as needed
    sprintf(numStr, "%d", number);
    int power = strlen(numStr);
    int sum = 0;
    for (int i = 0; i < strlen(numStr); i++) {
        int digit = numStr[i] - '0';
        sum += pow(digit, power);
    }
    return sum == number;
}

int main() {
    printf("%d\n", isNarcissistic(153)); // 1
    printf("%d\n", isNarcissistic(1652)); // 0
    printf("%d\n", isNarcissistic(7)); // 1
    printf("%d\n", isNarcissistic(371)); // 1
    printf("%d\n", isNarcissistic(4887)); // 0
    return 0;
}