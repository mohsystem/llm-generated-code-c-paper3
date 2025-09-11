#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    int prefixSum[numsSize + 1];
    int queue[numsSize + 1];
    int front = 0, rear = -1;
    int minLength = INT_MAX;

    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    for (int i = 0; i <= numsSize; i++) {
        while (front <= rear && prefixSum[i] - prefixSum[queue[front]] >= k) {
            minLength = fmin(minLength, i - queue[front]);
            front++;
        }

        while (front <= rear && prefixSum[i] <= prefixSum[queue[rear]]) {
            rear--;
        }

        rear++;
        queue[rear] = i;
    }

    return minLength == INT_MAX ? -1 : minLength;
}

int main() {
    int nums1[] = {1};
    printf("%d\n", shortestSubarray(nums1, 1, 1));  // Output: 1

    int nums2[] = {1, 2};
    printf("%d\n", shortestSubarray(nums2, 2, 4));  // Output: -1

    int nums3[] = {2, -1, 2};
    printf("%d\n", shortestSubarray(nums3, 3, 3));  // Output: 3

    return 0;
}