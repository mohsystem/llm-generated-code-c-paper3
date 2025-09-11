#include<stdio.h>

int findMissingNumber(int numbers[], int size) {
    int n = size + 1;
    int sum = n * (n + 1) / 2;
    int arraySum = 0;
    for (int i = 0; i < size; i++) {
        arraySum += numbers[i];
    }
    return sum - arraySum;
}

int main() {
    int test1[] = {1, 2, 4, 5};
    printf("%d\n", findMissingNumber(test1, 4)); // Output: 3

    int test2[] = {3, 4, 5, 6, 7, 8, 10};
    printf("%d\n", findMissingNumber(test2, 7)); // Output: 9
    return 0;
}