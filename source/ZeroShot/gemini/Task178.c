#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    int n = numsSize;
    long long* prefixSum = (long long*)malloc((n + 1) * sizeof(long long));
    prefixSum[0] = 0;
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int minLength = INT_MAX;
    int* deque = (int*)malloc((n + 1) * sizeof(int));
    int head = 0, tail = 0;

    for (int i = 0; i <= n; i++) {
        while (head < tail && prefixSum[i] - prefixSum[deque[head]] >= k) {
            minLength = (minLength < (i - deque[head])) ? minLength : (i - deque[head]);
            head++;
        }
        while (head < tail && prefixSum[i] <= prefixSum[deque[tail - 1]]) {
            tail--;
        }
        deque[tail++] = i;
    }

    free(prefixSum);
    free(deque);
    return minLength == INT_MAX ? -1 : minLength;
}

int main() {
    int nums1[] = {1};
    int k1 = 1;
    printf("%d\n", shortestSubarray(nums1, 1, k1)); // Output: 1

    int nums2[] = {1, 2};
    int k2 = 4;
    printf("%d\n", shortestSubarray(nums2, 2, k2)); // Output: -1

    int nums3[] = {2, -1, 2};
    int k3 = 3;
    printf("%d\n", shortestSubarray(nums3, 3, k3)); // Output: 3

    int nums4[] = {1, 2, 3, 4, 5};
    int k4 = 11;
    printf("%d\n", shortestSubarray(nums4, 5, k4)); // Output: 3

    int nums5[] = {1, -1, 2, -2, 3};
    int k5 = 3;
    printf("%d\n", shortestSubarray(nums5, 5, k5)); // Output: 1

    return 0;
}