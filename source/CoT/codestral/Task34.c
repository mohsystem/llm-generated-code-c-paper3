#include <stdio.h>
#include <math.h>

int isNarcissistic(int number) {
    int originalNumber = number, remainder, result = 0, n = 0;

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
    printf("%d\n", isNarcissistic(153));   // 1 (true)
    printf("%d\n", isNarcissistic(370));   // 1 (true)
    printf("%d\n", isNarcissistic(371));   // 1 (true)
    printf("%d\n", isNarcissistic(407));   // 1 (true)
    printf("%d\n", isNarcissistic(1652));  // 0 (false)
    return 0;
}