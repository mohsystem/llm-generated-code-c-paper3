#include <stdio.h>
#include <stdlib.h>

int findMissingNumber(int nums[], int n) {
    int expectedSum = (n + 1) * (n + 2) / 2;
    int actualSum = 0;
    for (int i = 0; i < n; i++) {
        actualSum += nums[i];
    }
    return expectedSum - actualSum;
}

int main() {
    int test1[] = {1, 2, 4, 5};
    printf("%d\n", findMissingNumber(test1, 4)); // Output: 3

    int test2[] = {1, 2, 3, 5, 6};
    printf("%d\n", findMissingNumber(test2, 5)); // Output: 4

    int test3[] = {2, 3, 4, 5, 6};
    printf("%d\n", findMissingNumber(test3, 5)); // Output: 1

    int test4[] = {1, 3, 4, 5, 6};
    printf("%d\n", findMissingNumber(test4, 5)); // Output: 2

    int test5[] = {1, 2, 3, 4, 6, 7, 8, 9, 10};
    printf("%d\n", findMissingNumber(test5, 9)); // Output: 5

    return 0;
}