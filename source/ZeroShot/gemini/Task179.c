#include <stdio.h>
#include <stdlib.h>

// Structure for a double-ended queue (deque)
typedef struct {
    int *arr;
    int front, rear, capacity;
} Deque;

// Function to create a new deque
Deque* createDeque(int capacity) {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->capacity = capacity;
    dq->front = -1;
    dq->rear = -1;
    dq->arr = (int*)malloc(capacity * sizeof(int));
    return dq;
}

// Function to check if the deque is empty
int isEmpty(Deque* dq) {
    return dq->front == -1;
}

// Function to add an element to the rear of the deque
void push_back(Deque* dq, int x) {
    if (dq->rear == dq->capacity - 1) {
      return; // Handle deque full condition if necessary
    }
    if (isEmpty(dq)) {
        dq->front = 0;
    }
    dq->rear++;
    dq->arr[dq->rear] = x;
}

// Function to remove the front element from the deque
void pop_front(Deque* dq) {
    if (isEmpty(dq)) {
        return;
    }
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    } else {
        dq->front++;
    }
}

// Function to remove the rear element from the deque
void pop_back(Deque* dq) {
    if (isEmpty(dq)) {
        return;
    }
    if (dq->front == dq->rear) {
        dq->front = -1;
        dq->rear = -1;
    } else {
        dq->rear--;
    }
}


// Function to get the front element of the deque
int front(Deque* dq) {
    if (isEmpty(dq)) {
        return -1; // Or handle the empty deque case as needed
    }
    return dq->arr[dq->front];
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k <= 0) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    *returnSize = numsSize - k + 1;
    Deque* dq = createDeque(numsSize);

    for (int i = 0; i < numsSize; i++) {
        while (!isEmpty(dq) && front(dq) < i - k + 1) {
            pop_front(dq);
        }
        while (!isEmpty(dq) && nums[dq->arr[dq->rear]] < nums[i]) {
            pop_back(dq);
        }
        push_back(dq, i);
        if (i >= k - 1) {
            result[i - k + 1] = nums[front(dq)];
        }
    }
    free(dq->arr);
    free(dq);
    return result;
}

int main() {
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    int returnSize1;
    int* result1 = maxSlidingWindow(nums1, sizeof(nums1) / sizeof(nums1[0]), k1, &returnSize1);
    for (int i = 0; i < returnSize1; i++) printf("%d ", result1[i]); // Output: 3 3 5 5 6 7
    printf("\n");
    free(result1);


    int nums2[] = {1};
    int k2 = 1;
    int returnSize2;
    int* result2 = maxSlidingWindow(nums2, sizeof(nums2) / sizeof(nums2[0]), k2, &returnSize2);
    for (int i = 0; i < returnSize2; i++) printf("%d ", result2[i]); // Output: 1
    printf("\n");
    free(result2);

    int nums3[] = {1, -1};
    int k3 = 1;
    int returnSize3;
    int* result3 = maxSlidingWindow(nums3, sizeof(nums3) / sizeof(nums3[0]), k3, &returnSize3);
    for (int i = 0; i < returnSize3; i++) printf("%d ", result3[i]); // Output: 1 -1
    printf("\n");
    free(result3);


    int nums4[] = {9, 10, 9, -7, -4, -8, 2, -6};
    int k4 = 5;
    int returnSize4;
    int* result4 = maxSlidingWindow(nums4, sizeof(nums4) / sizeof(nums4[0]), k4, &returnSize4);
    for (int i = 0; i < returnSize4; i++) printf("%d ", result4[i]); // Output: 10 10 9 2
    printf("\n");
    free(result4);

    int nums5[] = {1, 3, 1, 2, 0, 5};
    int k5 = 3;
    int returnSize5;
    int* result5 = maxSlidingWindow(nums5, sizeof(nums5) / sizeof(nums5[0]), k5, &returnSize5);
    for (int i = 0; i < returnSize5; i++) printf("%d ", result5[i]); // Output: 3 3 2 5
    printf("\n");
    free(result5);


    return 0;
}