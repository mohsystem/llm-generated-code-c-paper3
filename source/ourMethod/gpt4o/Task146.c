#include <stdio.h>

int findMissingNumber(const int numbers[], int size, int n) {
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;
    for (int i = 0; i < size; i++) {
        actualSum += numbers[i];
    }
    return expectedSum - actualSum;
}

int main() {
    printf("%d\n", findMissingNumber((int[]){1, 2, 4, 5, 6}, 5, 6)); // Output: 3
    printf("%d\n", findMissingNumber((int[]){1, 3}, 2, 3)); // Output: 2
    printf("%d\n", findMissingNumber((int[]){2, 3, 4, 5}, 4, 5)); // Output: 1
    printf("%d\n", findMissingNumber((int[]){1, 2, 3, 5}, 4, 5)); // Output: 4
    printf("%d\n", findMissingNumber((int[]){1}, 1, 2)); // Output: 2
    return 0;
}