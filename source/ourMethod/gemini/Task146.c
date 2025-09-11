#include <stdio.h>

int findMissingNumber(int nums[], int n) {
    int expectedSum = (n + 1) * (n + 2) / 2;
    int actualSum = 0;
    for (int i = 0; i < n; i++) {
        actualSum += nums[i];
    }
    return expectedSum - actualSum;
}

int main() {
    // Test cases
    int test1[] = {1, 2, 3, 4, 6};
    int missing1 = findMissingNumber(test1, 5);
    printf("Missing number: %d\n", missing1); // Expected: 5

    int test2[] = {1, 2, 4, 5, 6};
    int missing2 = findMissingNumber(test2, 5);
    printf("Missing number: %d\n", missing2); // Expected: 3

    int test3[] = {2, 3, 4, 5, 6};
    int missing3 = findMissingNumber(test3, 5);
    printf("Missing number: %d\n", missing3); // Expected: 1

    int test4[] = {1, 2, 3, 4, 5};
    int missing4 = findMissingNumber(test4, 5);
    printf("Missing number: %d\n", missing4); // Expected: 6

    int test5[] = {1};
    int missing5 = findMissingNumber(test5, 1);
    printf("Missing number: %d\n", missing5); // Expected: 2


    return 0;
}