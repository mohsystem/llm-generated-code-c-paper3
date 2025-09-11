#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

bool isNarcissistic(int number) {
    char numStr[20]; // Adjust size as needed
    sprintf(numStr, "%d", number);
    int power = strlen(numStr);
    int sum = 0;
    for (int i = 0; i < power; i++) {
        int digit = numStr[i] - '0';
        sum += pow(digit, power);
    }
    return sum == number;
}

int main() {
    printf("%s\n", isNarcissistic(153) ? "true" : "false"); // true
    printf("%s\n", isNarcissistic(1652) ? "true" : "false"); // false
    printf("%s\n", isNarcissistic(1) ? "true" : "false"); // true
    printf("%s\n", isNarcissistic(407) ? "true" : "false"); // true
    printf("%s\n", isNarcissistic(1634) ? "true" : "false"); // true

    return 0;
}