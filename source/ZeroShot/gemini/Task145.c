#include <stdio.h>
#include <limits.h>

int maxSubArraySum(int nums[], int n) {
    if (n <= 0) {
        return 0;
    }

    int maxSoFar = INT_MIN;
    int currentMax = 0;

    for (int i = 0; i < n; i++) {
        currentMax = (nums[i] > currentMax + nums[i]) ? nums[i] : currentMax + nums[i];
        maxSoFar = (maxSoFar > currentMax) ? maxSoFar : currentMax;
    }

    return maxSoFar;
}

int main() {
    int test1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int test2[] = {1};
    int test3[] = {5, 4, -1, 7, 8};
    int test4[] = {-1};
    int test5[] = {-2, -1};

    printf("%d\n", maxSubArraySum(test1, sizeof(test1) / sizeof(test1[0]))); // Output: 6
    printf("%d\n", maxSubArraySum(test2, sizeof(test2) / sizeof(test2[0]))); // Output: 1
    printf("%d\n", maxSubArraySum(test3, sizeof(test3) / sizeof(test3[0]))); // Output: 23
    printf("%d\n", maxSubArraySum(test4, sizeof(test4) / sizeof(test4[0]))); // Output: -1
    printf("%d\n", maxSubArraySum(test5, sizeof(test5) / sizeof(test5[0]))); // Output: -1

    return 0;
}