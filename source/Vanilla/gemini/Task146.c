#include <stdio.h>

int findMissingNumber(int nums[], int n) {
    int len = n;
    n = len + 1;
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;
    for (int i = 0; i < len; i++) {
        actualSum += nums[i];
    }
    return expectedSum - actualSum;
}

int main() {
    int test1[] = {1, 2, 4, 5};
    int test2[] = {1, 2, 3, 4, 6};
    int test3[] = {2, 3, 4, 5};
    int test4[] = {1, 3, 4, 5, 6};
    int test5[] = {1};

    printf("%d\n", findMissingNumber(test1, 4)); // Output: 3
    printf("%d\n", findMissingNumber(test2, 5)); // Output: 5
    printf("%d\n", findMissingNumber(test3, 4)); // Output: 1
    printf("%d\n", findMissingNumber(test4, 5)); // Output: 2
    printf("%d\n", findMissingNumber(test5, 1)); // Output: 2
    return 0;
}