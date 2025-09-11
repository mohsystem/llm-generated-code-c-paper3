#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

bool isNarcissistic(int number) {
    char str[20];
    sprintf(str, "%d", number);
    int n = strlen(str);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (int) pow(str[i] - '0', n);
    }
    return sum == number;
}

int main() {
    printf("%d\n", isNarcissistic(153)); // 1 (true)
    printf("%d\n", isNarcissistic(1652)); // 0 (false)
    printf("%d\n", isNarcissistic(407)); // 1 (true)
    printf("%d\n", isNarcissistic(1634)); // 1 (true)
    printf("%d\n", isNarcissistic(8208)); // 1 (true)
    return 0;
}