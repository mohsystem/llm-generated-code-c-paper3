#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    int* prefixSum = (int*)malloc((numsSize + 1) * sizeof(int));
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int shortest = INT_MAX;
    int deque[numsSize + 1];
    int front = 0, rear = 0;
    for (int i = 0; i <= numsSize; i++) {
        while (front < rear && prefixSum[i] - prefixSum[deque[front]] >= k) {
            shortest = fmin(shortest, i - deque[front]);
            front++;
        }
        while (front < rear && prefixSum[i] <= prefixSum[deque[rear - 1]]) {
            rear--;
        }
        deque[rear++] = i;
    }

    free(prefixSum);
    return shortest == INT_MAX ? -1 : shortest;
}

int main() {
    int nums1[] = {1};
    int nums2[] = {1, 2};
    int nums3[] = {2, -1, 2};
    printf("%d\n", shortestSubarray(nums1, 1, 1)); // Output: 1
    printf("%d\n", shortestSubarray(nums2, 2, 4)); // Output: -1
    printf("%d\n", shortestSubarray(nums3, 3, 3)); // Output: 3
    return 0;
}