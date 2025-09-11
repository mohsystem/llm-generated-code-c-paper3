#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int shortestSubarray(int* nums, int numsSize, int k) {
    int n = numsSize;
    long long* prefixSum = (long long*)malloc((n + 1) * sizeof(long long));
    
    if (prefixSum == NULL) {
        return -1; // Handle memory allocation failure
    }


    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int minLen = INT_MAX;
    int* dq = (int*)malloc((n + 1) * sizeof(int));
    int front = 0, rear = 0;

        if (dq == NULL) {
            free(prefixSum); // Free previously allocated memory
            return -1; // Handle memory allocation failure
        }

    for (int i = 0; i <= n; i++) {
        while ((rear - front) > 0 && prefixSum[i] - prefixSum[dq[front]] >= k) {
            minLen = (minLen < (i - dq[front])) ? minLen : (i - dq[front]);
            front++;
        }
        while ((rear-front) > 0 && prefixSum[i] <= prefixSum[dq[rear-1]]) {
            rear--;
        }
        dq[rear++] = i;
    }

    free(prefixSum);
    free(dq);

    return minLen == INT_MAX ? -1 : minLen;
}

int main() {
    int nums1[] = {1};
    int k1 = 1;
    printf("%d\n", shortestSubarray(nums1, 1, k1)); // 1

    int nums2[] = {1, 2};
    int k2 = 4;
    printf("%d\n", shortestSubarray(nums2, 2, k2)); // -1

    int nums3[] = {2, -1, 2};
    int k3 = 3;
    printf("%d\n", shortestSubarray(nums3, 3, k3)); // 3

    int nums4[] = {1, 1, 1, 1, 1, 10};
    int k4 = 11;
    printf("%d\n", shortestSubarray(nums4, 6, k4)); // 2

    int nums5[] = {84, -37, 32, 40, 95};
    int k5 = 167;
    printf("%d\n", shortestSubarray(nums5, 5, k5)); // 3

    return 0;
}