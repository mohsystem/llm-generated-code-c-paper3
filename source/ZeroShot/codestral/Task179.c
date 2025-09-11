#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100005

int deq[MAX_SIZE];
int front = 0, rear = -1;

void push(int x) {
    deq[++rear] = x;
}

void pop_front() {
    front++;
}

int front_val() {
    return deq[front];
}

void pop_back() {
    rear--;
}

int back_val() {
    return deq[rear];
}

int empty() {
    return front > rear;
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    int n = numsSize;
    int* output = (int*)malloc(sizeof(int) * (n - k + 1));
    *returnSize = n - k + 1;

    for (int i = 0; i < n; i++) {
        if (!empty() && front_val() < i - k + 1) {
            pop_front();
        }

        while (!empty() && nums[back_val()] < nums[i]) {
            pop_back();
        }

        push(i);

        if (i >= k - 1) {
            output[i - k + 1] = nums[front_val()];
        }
    }

    return output;
}

int main() {
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int returnSize1;
    int* result1 = maxSlidingWindow(nums1, 8, 3, &returnSize1);
    for(int i = 0; i < returnSize1; i++) printf("%d ", result1[i]);
    printf("\n");
    free(result1);

    int nums2[] = {1};
    int returnSize2;
    int* result2 = maxSlidingWindow(nums2, 1, 1, &returnSize2);
    for(int i = 0; i < returnSize2; i++) printf("%d ", result2[i]);
    printf("\n");
    free(result2);

    return 0;
}