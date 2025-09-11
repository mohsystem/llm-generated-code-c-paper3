#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    long long* prefixSum = (long long*)malloc((numsSize + 1) * sizeof(long long));
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int minLen = INT_MAX;
    int* deque = (int*)malloc((numsSize + 1) * sizeof(int));
    int head = 0, tail = 0;

    for (int i = 0; i <= numsSize; i++) {
        while (head < tail && prefixSum[i] - prefixSum[deque[head]] >= k) {
            minLen = (minLen < i - deque[head]) ? minLen : (i - deque[head]);
            head++;
        }
        while (head < tail && prefixSum[i] <= prefixSum[deque[tail - 1]]) {
            tail--;
        }
        deque[tail++] = i;
    }

    free(prefixSum);
    free(deque);
    return (minLen == INT_MAX) ? -1 : minLen;
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

    int nums4[] = {84,-37,32,40,95};
    int k4 = 167;
    printf("%d\n", shortestSubarray(nums4, 5, k4)); // Output: 3

    int nums5[] = {1};
    int k5 = 2;
    printf("%d\n", shortestSubarray(nums5, 1, k5)); // Output: -1

    return 0;
}