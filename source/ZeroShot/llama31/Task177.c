#include <stdio.h>
#include <stdlib.h>

int constrainedSubsetSum(int* nums, int n, int k) {
    int* dp = (int*)malloc(n * sizeof(int));
    dp[0] = nums[0];
    int max_sum = nums[0];
    int* queue = (int*)malloc((k + 1) * sizeof(int));
    int front = 0, rear = 0;
    queue[rear++] = 0;

    for (int i = 1; i < n; i++) {
        if (front == rear) {
            front = rear = 0;
            queue[rear++] = i;
            dp[i] = nums[i];
        } else {
            int idx = queue[front];
            dp[i] = (dp[idx] + nums[i] > nums[i]) ? dp[idx] + nums[i] : nums[i];
            while (rear > front && i - queue[front] > k) {
                front++;
            }
            while (rear > front && dp[queue[rear - 1]] < dp[i]) {
                rear--;
            }
            queue[rear++] = i;
        }
        if (dp[i] > max_sum) {
            max_sum = dp[i];
        }
    }
    free(dp);
    free(queue);
    return max_sum;
}

int main() {
    int testCases[][5] = {
        {10, 2, -10, 5, 20},
        {-1, -2, -3},
        {10, -2, -10, -5, 20}
    };
    int ks[] = {2, 1, 2};
    int sizes[] = {5, 3, 5};

    for (int i = 0; i < 3; i++) {
        printf("%d\n", constrainedSubsetSum(testCases[i], sizes[i], ks[i]));
    }
    return 0;
}