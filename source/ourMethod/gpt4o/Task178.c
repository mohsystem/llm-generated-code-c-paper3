#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    long* prefixSum = (long*)calloc(numsSize + 1, sizeof(long));
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int minLength = numsSize + 1;
    int* deque = (int*)malloc((numsSize + 1) * sizeof(int));
    int front = 0, back = 0;

    for (int i = 0; i <= numsSize; i++) {
        while (front < back && prefixSum[i] - prefixSum[deque[front]] >= k) {
            minLength = i - deque[front];
            front++;
        }

        while (front < back && prefixSum[i] <= prefixSum[deque[back - 1]]) {
            back--;
        }

        deque[back++] = i;
    }

    free(prefixSum);
    free(deque);

    return minLength <= numsSize ? minLength : -1;
}

int main() {
    int nums1[] = {1};
    int nums2[] = {1, 2};
    int nums3[] = {2, -1, 2};
    int nums4[] = {2, 1, -1, 2, 3};
    int nums5[] = {-1, -2, -3, 4, 5};

    printf("%d\n", shortestSubarray(nums1, 1, 1)); // Output: 1
    printf("%d\n", shortestSubarray(nums2, 2, 4)); // Output: -1
    printf("%d\n", shortestSubarray(nums3, 3, 3)); // Output: 3
    printf("%d\n", shortestSubarray(nums4, 5, 5)); // Example additional case
    printf("%d\n", shortestSubarray(nums5, 5, 3)); // Example additional case

    return 0;
}