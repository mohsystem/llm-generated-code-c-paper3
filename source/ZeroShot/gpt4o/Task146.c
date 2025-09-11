#include <stdio.h>

int findMissingNumber(int arr[], int n) {
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;
    for (int i = 0; i < n - 1; i++) {
        actualSum += arr[i];
    }
    return expectedSum - actualSum;
}

int main() {
    int test1[] = {1, 2, 3, 5};
    int test2[] = {1, 3, 4, 5};
    int test3[] = {2, 3, 4, 5};
    int test4[] = {1, 2, 4, 5};
    int test5[] = {1, 2, 3, 4};

    printf("%d\n", findMissingNumber(test1, 5)); // Output: 4
    printf("%d\n", findMissingNumber(test2, 5)); // Output: 2
    printf("%d\n", findMissingNumber(test3, 5)); // Output: 1
    printf("%d\n", findMissingNumber(test4, 5)); // Output: 3
    printf("%d\n", findMissingNumber(test5, 5)); // Output: 5

    return 0;
}