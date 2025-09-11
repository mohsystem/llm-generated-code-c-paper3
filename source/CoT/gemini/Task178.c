#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    long long* prefixSum = (long long*)malloc((numsSize + 1) * sizeof(long long));
    if (prefixSum == NULL) {
        return -1; // Memory allocation failed
    }
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int minLength = INT_MAX;
    int* deque = (int*)malloc((numsSize + 1) * sizeof(int));
    if (deque == NULL) {
        free(prefixSum);
        return -1; // Memory allocation failed
    }
    int head = 0, tail = 0;

    for (int i = 0; i <= numsSize; i++) {
        while (head < tail && prefixSum[i] <= prefixSum[deque[tail - 1]]) {
            tail--;
        }
        while (head < tail && prefixSum[i] - prefixSum[deque[head]] >= k) {
            minLength = (minLength < i - deque[head]) ? minLength : (i - deque[head]);
            head++;
        }
        deque[tail++] = i;
    }

    free(prefixSum);
    free(deque);
    return (minLength == INT_MAX) ? -1 : minLength;
}

int main() {
    int nums1[] = {1};
    printf("%d\n", shortestSubarray(nums1, 1, 1)); // Output: 1

    int nums2[] = {1, 2};
    printf("%d\n", shortestSubarray(nums2, 2, 4)); // Output: -1

    int nums3[] = {2, -1, 2};
    printf("%d\n", shortestSubarray(nums3, 3, 3)); // Output: 3

    int nums4[] = {1, 2, 3, 4, 5};
    printf("%d\n", shortestSubarray(nums4, 5, 10)); // Output: 3
    
    int nums5[] = {-1, -1, 2, 3};
    printf("%d\n", shortestSubarray(nums5, 4, 5)); // Output: -1

    return 0;
}