#include <stdio.h>

int findMissingNumber(int numbers[], int size, int n) {
    int totalSum = n * (n + 1) / 2;
    int arraySum = 0;
    for (int i = 0; i < size; ++i) {
        arraySum += numbers[i];
    }
    return totalSum - arraySum;
}

int main() {
    int numbers1[] = {1, 2, 4, 5, 6};
    printf("%d\n", findMissingNumber(numbers1, 5, 6)); // Output: 3

    int numbers2[] = {2, 3, 4, 5, 6};
    printf("%d\n", findMissingNumber(numbers2, 5, 6)); // Output: 1

    int numbers3[] = {1, 3, 4, 5, 6};
    printf("%d\n", findMissingNumber(numbers3, 5, 6)); // Output: 2

    int numbers4[] = {1, 2, 3, 5, 6};
    printf("%d\n", findMissingNumber(numbers4, 5, 6)); // Output: 4

    int numbers5[] = {1, 2, 3, 4, 6};
    printf("%d\n", findMissingNumber(numbers5, 5, 6)); // Output: 5

    return 0;
}