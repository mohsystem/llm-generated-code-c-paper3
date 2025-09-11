#include<stdio.h>

int getSum(int a, int b) {
    if (a == b)
        return a;

    int minVal = (a < b) ? a : b;
    int maxVal = (a > b) ? a : b;
    int sum = 0;

    for (int i = minVal; i <= maxVal; i++) {
        sum += i;
    }

    return sum;
}

int main() {
    printf("%d\n", getSum(1, 0));  // 1
    printf("%d\n", getSum(1, 2));  // 3
    printf("%d\n", getSum(0, 1));  // 1
    printf("%d\n", getSum(1, 1));  // 1
    printf("%d\n", getSum(-1, 2));  // 2
    return 0;
}