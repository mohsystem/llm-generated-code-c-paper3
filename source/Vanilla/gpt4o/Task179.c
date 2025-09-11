#include <stdio.h>
#include <stdlib.h>

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    int* deq = (int*)malloc(numsSize * sizeof(int));
    int front = 0, back = 0;

    for (int i = 0; i < numsSize; ++i) {
        if (front < back && deq[front] < i - k + 1) {
            front++;
        }
        while (front < back && nums[deq[back - 1]] < nums[i]) {
            back--;
        }
        deq[back++] = i;
        if (i >= k - 1) {
            result[i - k + 1] = nums[deq[front]];
        }
    }

    free(deq);
    *returnSize = numsSize - k + 1;
    return result;
}

void printArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int nums1[] = {1,3,-1,-3,5,3,6,7};
    int k1 = 3;
    int returnSize1;
    int* result1 = maxSlidingWindow(nums1, 8, k1, &returnSize1);
    printArray(result1, returnSize1); // Output: [3,3,5,5,6,7]
    free(result1);

    int nums2[] = {1};
    int k2 = 1;
    int returnSize2;
    int* result2 = maxSlidingWindow(nums2, 1, k2, &returnSize2);
    printArray(result2, returnSize2); // Output: [1]
    free(result2);

    int nums3[] = {9, 11};
    int k3 = 2;
    int returnSize3;
    int* result3 = maxSlidingWindow(nums3, 2, k3, &returnSize3);
    printArray(result3, returnSize3); // Output: [11]
    free(result3);

    int nums4[] = {4, -2};
    int k4 = 2;
    int returnSize4;
    int* result4 = maxSlidingWindow(nums4, 2, k4, &returnSize4);
    printArray(result4, returnSize4); // Output: [4]
    free(result4);

    int nums5[] = {7, 2, 4};
    int k5 = 2;
    int returnSize5;
    int* result5 = maxSlidingWindow(nums5, 3, k5, &returnSize5);
    printArray(result5, returnSize5); // Output: [7, 4]
    free(result5);

    return 0;
}