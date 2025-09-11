#include <stdio.h>

int findMissingNumber(int* nums, int n) {
    int total = (n + 1) * (n + 2) / 2;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
    }
    return total - sum;
}

int main() {
    int nums[] = {1, 2, 3, 5, 6};
    int n = sizeof(nums) / sizeof(nums[0]);
    printf("%d\n", findMissingNumber(nums, n));
    return 0;
}