#include <stdio.h>
#include <math.h>
#include <string.h>

bool isNarcissistic(int n) {
    char str[100];
    sprintf(str, "%d", n);
    int length = strlen(str);
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += (int) pow(str[i] - '0', length);
    }
    return sum == n;
}

int main() {
    printf("%d\n", isNarcissistic(153)); // 1 (true)
    printf("%d\n", isNarcissistic(1652)); // 0 (false)
    printf("%d\n", isNarcissistic(1634)); // 1 (true)
    printf("%d\n", isNarcissistic(8208)); // 1 (true)
    printf("%d\n", isNarcissistic(9474)); // 1 (true)
    return 0;
}