#include<stdio.h>
#include<math.h>

int isNarcissistic(int number) {
    int originalNumber, result = 0, remainder, n = 0;

    originalNumber = number;

    while (originalNumber != 0) {
        originalNumber /= 10;
        ++n;
    }

    originalNumber = number;

    while (originalNumber != 0) {
        remainder = originalNumber % 10;
        result += pow(remainder, n);
        originalNumber /= 10;
    }

    return number == result;
}

int main() {
    printf("%d\n", isNarcissistic(153)); // 1 (true)
    printf("%d\n", isNarcissistic(1652)); // 0 (false)
    printf("%d\n", isNarcissistic(1151322190187639925)); // 0 (false)
    printf("%d\n", isNarcissistic(4887)); // 0 (false)
    printf("%d\n", isNarcissistic(9474)); // 1 (true)
    return 0;
}