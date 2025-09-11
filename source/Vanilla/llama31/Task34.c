#include <stdio.h>
#include <math.h>
#include <string.h>

bool isNarcissistic(int n) {
    char str[100];
    sprintf(str, "%d", n);
    int digits = strlen(str);
    int sum = 0;
    for (int i = 0; i < digits; i++) {
        sum += pow(str[i] - '0', digits);
    }
    return sum == n;
}

int main() {
    printf("%d\n", isNarcissistic(153));   // 1 (true)
    printf("%d\n", isNarcissistic(1652));  // 0 (false)
    printf("%d\n", isNarcissistic(407));   // 1 (true)
    printf("%d\n", isNarcissistic(1634));  // 1 (true)
    printf("%d\n", isNarcissistic(8208));  // 1 (true)
    return 0;
}