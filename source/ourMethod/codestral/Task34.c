#include<stdio.h>
#include<math.h>
#include<string.h>

int isNarcissistic(int number) {
    int originalNumber, result = 0, remainder;
    int n = snprintf(0, 0, "%d", number);

    originalNumber = number;

    while (originalNumber != 0) {
        remainder = originalNumber % 10;
        result += pow(remainder, n);
        originalNumber /= 10;
    }

    return number == result;
}

int main() {
    printf("%d\n", isNarcissistic(153));  // 1 (true)
    printf("%d\n", isNarcissistic(1652));  // 0 (false)
    printf("%d\n", isNarcissistic(1634));  // 1 (true)
    printf("%d\n", isNarcissistic(8208));  // 1 (true)
    printf("%d\n", isNarcissistic(9474));  // 0 (false)
    return 0;
}