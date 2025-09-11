// Note: C does not support dynamic arrays or dequeues directly.
// This implementation uses a simple array to simulate the deque.
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

int* maxSlidingWindow(int* nums, int n, int k, int* resultSize) {
    if (n == 0) {
        *resultSize = 0;
        return NULL;
    }
    int* result = (int*)malloc((n - k + 1) * sizeof(int));
    int dq[MAX_SIZE];
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++) {
        // Remove elements from the back of the deque that are out of the current window
        while (front < rear && dq[front] < i - k + 1) {
            front++;
        }
        // Remove elements from the front of the deque that are smaller than the current element
        while (front < rear && nums[dq[rear - 1]] < nums[i]) {
            rear--;
        }
        dq[rear++] = i;
        // Add the maximum element of the current window to the result
        if (i >= k - 1) {
            result[i - k + 1] = nums[dq[front]];
        }
    }
    *resultSize = n - k + 1;
    return result;
}

int main() {
    // Test cases
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    int n1 = sizeof(nums1) / sizeof(nums1[0]);
    int resultSize1;
    int* result1 = maxSlidingWindow(nums1, n1, k1, &resultSize1);
    for (int i = 0; i < resultSize1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");

    int nums2[] = {1};
    int k2 = 1;
    int n2 = sizeof(nums2) / sizeof(nums2[0]);
    int resultSize2;
    int* result2 = maxSlidingWindow(nums2, n2, k2, &resultSize2);
    for (int i = 0; i < resultSize2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");

    int nums3[] = {1, 2, 3, 4, 5};
    int k3 = 2;
    int n3 = sizeof(nums3) / sizeof(nums3[0]);
    int resultSize3;
    int* result3 = maxSlidingWindow(nums3, n3, k3, &resultSize3);
    for (int i = 0; i < resultSize3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n");

    int nums4[] = {5, 4, 3, 2, 1};
    int k4 = 2;
    int n4 = sizeof(nums4) / sizeof(nums4[0]);
    int resultSize4;
    int* result4 = maxSlidingWindow(nums4, n4, k4, &resultSize4);
    for (int i = 0; i < resultSize4; i++) {
        printf("%d ", result4[i]);
    }
    printf("\n");

    int nums5[] = {1, 1, 1, 1, 1};
    int k5 = 3;
    int n5 = sizeof(nums5) / sizeof(nums5[0]);
    int resultSize5;
    int* result5 = maxSlidingWindow(nums5, n5, k5, &resultSize5);
    for (int i = 0; i < resultSize5; i++) {
        printf("%d ", result5[i]);
    }
    printf("\n");

    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);

    return 0;
}