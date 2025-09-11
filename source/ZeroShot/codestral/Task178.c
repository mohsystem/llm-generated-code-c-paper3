#include <stdio.h>
#include <stdlib.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    int* prefixSum = (int*)malloc((numsSize + 1) * sizeof(int));
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int result = numsSize + 1;
    int* deque = (int*)malloc(numsSize * sizeof(int));
    int front = 0, rear = 0;
    for (int i = 0; i <= numsSize; i++) {
        while (front < rear && prefixSum[i] - prefixSum[deque[front]] >= k) {
            result = result < i - deque[front] ? result : i - deque[front];
            front++;
        }
        while (front < rear && prefixSum[i] <= prefixSum[deque[rear - 1]]) {
            rear--;
        }
        deque[rear++] = i;
    }

    free(prefixSum);
    free(deque);

    return result > numsSize ? -1 : result;
}

int main() {
    int nums1[] = {1};
    int k1 = 1;
    printf("%d\n", shortestSubarray(nums1, 1, k1));

    int nums2[] = {1,2};
    int k2 = 4;
    printf("%d\n", shortestSubarray(nums2, 2, k2));

    int nums3[] = {2,-1,2};
    int k3 = 3;
    printf("%d\n", shortestSubarray(nums3, 3, k3));

    return 0;
}