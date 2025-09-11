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
    printf("%s\n", isNarcissistic(7) ? "true" : "false"); // true
    printf("%s\n", isNarcissistic(371) ? "true" : "false"); // true
    printf("%s\n", isNarcissistic(4887) ? "true" : "false"); // false
    return 0;
}