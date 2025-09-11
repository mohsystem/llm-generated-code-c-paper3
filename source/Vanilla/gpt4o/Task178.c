#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    long* prefixSum = (long*)calloc(numsSize + 1, sizeof(long));
    for (int i = 0; i < numsSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int minLength = INT_MAX;
    int* dq = (int*)malloc((numsSize + 1) * sizeof(int));
    int front = 0, back = 0;

    for (int i = 0; i <= numsSize; ++i) {
        while (front < back && prefixSum[i] - prefixSum[dq[front]] >= k) {
            if (i - dq[front] < minLength) {
                minLength = i - dq[front];
            }
            front++;
        }
        while (front < back && prefixSum[i] <= prefixSum[dq[back - 1]]) {
            back--;
        }
        dq[back++] = i;
    }

    free(prefixSum);
    free(dq);
    return minLength == INT_MAX ? -1 : minLength;
}

int main() {
    int nums1[] = {1};
    printf("%d\n", shortestSubarray(nums1, 1, 1)); // Output: 1

    int nums2[] = {1, 2};
    printf("%d\n", shortestSubarray(nums2, 2, 4)); // Output: -1

    int nums3[] = {2, -1, 2};
    printf("%d\n", shortestSubarray(nums3, 3, 3)); // Output: 3

    int nums4[] = {84, -37, 32, 40, 95};
    printf("%d\n", shortestSubarray(nums4, 5, 167)); // Output: 3

    int nums5[] = {-28, 81, -20, 28, -29};
    printf("%d\n", shortestSubarray(nums5, 5, 89)); // Output: 3

    return 0;
}