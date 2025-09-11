#include<stdio.h>
#include<math.h>

int isNarcissistic(int number) {
    int originalNumber, result = 0, n = 0;

    originalNumber = number;

    while (originalNumber != 0) {
        originalNumber /= 10;
        ++n;
    }

    originalNumber = number;

    while (originalNumber != 0) {
        int digit = originalNumber % 10;
        result += pow(digit, n);
        originalNumber /= 10;
    }

    return number == result;
}

int main() {
    printf("%d\n", isNarcissistic(153));  // 1 (true)
    printf("%d\n", isNarcissistic(1652));  // 0 (false)
    printf("%d\n", isNarcissistic(115132219018763992565095597973971522401));  // 0 (false)
    printf("%d\n", isNarcissistic(4887));  // 0 (false)
    printf("%d\n", isNarcissistic(8208));  // 1 (true)
    return 0;
}