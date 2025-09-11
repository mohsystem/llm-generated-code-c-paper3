#include <stdio.h>
#include <stdlib.h>

int constrainedSubsetSum(int* nums, int n, int k) {
    int max_sum = nums[0];
    int* dp = (int*)malloc(n * sizeof(int));
    dp[0] = nums[0];
    int* queue = (int*)malloc((k + 1) * sizeof(int));
    int front = 0, rear = 0;
    queue[rear++] = 0;

    for (int i = 1; i < n; i++) {
        if (front == rear) {
            front = (front + 1) % (k + 1);
        }
        int prev = (front == 0) ? dp[queue[0]] : dp[queue[front]];
        dp[i] = (prev > 0) ? nums[i] + prev : nums[i];
        max_sum = (max_sum > dp[i]) ? max_sum : dp[i];

        while (rear > front && dp[queue[rear - 1]] <= dp[i]) {
            rear--;
        }
        queue[rear % (k + 1)] = i;
        rear = (rear + 1) % (k + 1);
    }

    free(dp);
    free(queue);
    return max_sum;
}

int main() {
    int nums1[] = {10, 2, -10, 5, 20};
    int k1 = 2;
    printf("%d\n", constrainedSubsetSum(nums1, 5, k1)); // Output: 37

    int nums2[] = {-1, -2, -3};
    int k2 = 1;
    printf("%d\n", constrainedSubsetSum(nums2, 3, k2)); // Output: -1

    int nums3[] = {10, -2, -10, -5, 20};
    int k3 = 2;
    printf("%d\n", constrainedSubsetSum(nums3, 5, k3)); // Output: 23

    int nums4[] = {5, -3, 5};
    int k4 = 2;
    printf("%d\n", constrainedSubsetSum(nums4, 3, k4)); // Output: 10

    int nums5[] = {-2, -3, -1};
    int k5 = 1;
    printf("%d\n", constrainedSubsetSum(nums5, 3, k5)); // Output: -1

    return 0;
}