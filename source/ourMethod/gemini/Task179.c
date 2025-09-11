#include <stdio.h>
#include <stdlib.h>

// Structure for a double-ended queue
typedef struct {
    int *arr;
    int front;
    int rear;
    int capacity;
} Deque;

// Function to create a new deque
Deque *createDeque(int capacity) {
    Deque *dq = (Deque *)malloc(sizeof(Deque));
    dq->arr = (int *)malloc(sizeof(int) * capacity);
    dq->front = -1;
    dq->rear = -1;
    dq->capacity = capacity;
    return dq;
}

// Function to check if the deque is empty
int isEmpty(Deque *dq) {
    return (dq->front == -1);
}

// Function to add an element to the rear of the deque
void push_back(Deque *dq, int value) {
    if (dq->rear == dq->capacity - 1) {
      return; // Handle deque full condition if needed. 
    }
    if(isEmpty(dq)){
        dq->front = 0;
    }
    dq->rear++;
    dq->arr[dq->rear] = value;

}

// Function to remove and return the front element of the deque
int pop_front(Deque *dq) {
    if (isEmpty(dq)) {
        return -1; // Or handle empty deque as appropriate
    }
    int val = dq->arr[dq->front];
    if(dq->front == dq->rear){
        dq->front = -1;
        dq->rear = -1;
    } else {
        dq->front++;
    }
    return val;
}

// Function to get the front element of the deque
int front(Deque *dq) {
   if (isEmpty(dq)) {
        return -1; // Or handle empty deque as appropriate
    }
    return dq->arr[dq->front];
}
// Function to remove the rear element of the deque
void pop_back(Deque *dq) {
    if (isEmpty(dq)) {
      return; // Handle empty deque as needed
    }
    if(dq->front == dq->rear){
        dq->front = -1;
        dq->rear = -1;
    } else {
        dq->rear--;
    }
}

// Function to free the deque's memory
void freeDeque(Deque *dq) {
    free(dq->arr);
    free(dq);
}



int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize){
    if (nums == NULL || k <= 0) {
        *returnSize = 0;
        return NULL;
    }
    int n = numsSize;
    int* result = (int*)malloc(sizeof(int) * (n - k + 1));
    *returnSize = n-k+1;
    Deque *dq = createDeque(n);


    for (int i = 0; i < n; i++) {
        while (!isEmpty(dq) && nums[i] >= nums[front(dq)]) {
            pop_back(dq);
        }
        push_back(dq, i);

        if (i >= k - 1) {
            result[i - k + 1] = nums[front(dq)];
            if (front(dq) == i - k + 1) {
                pop_front(dq);
            }
        }

    }
    freeDeque(dq);
    return result;

}

int main() {
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int numsSize1 = sizeof(nums1) / sizeof(nums1[0]);
    int k1 = 3;
    int returnSize1;
    int* result1 = maxSlidingWindow(nums1, numsSize1, k1, &returnSize1);
    for (int i = 0; i < returnSize1; i++) {
        printf("%d ", result1[i]); // Output: 3 3 5 5 6 7
    }
    printf("\n");
    free(result1);

    int nums2[] = {1};
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);
    int k2 = 1;
    int returnSize2;
    int* result2 = maxSlidingWindow(nums2, numsSize2, k2, &returnSize2);
    for (int i = 0; i < returnSize2; i++) {
        printf("%d ", result2[i]); // Output: 1
    }
    printf("\n");
    free(result2);

    int nums3[] = {1, -1};
    int numsSize3 = sizeof(nums3) / sizeof(nums3[0]);
    int k3 = 1;
    int returnSize3;
    int* result3 = maxSlidingWindow(nums3, numsSize3, k3, &returnSize3);
    for (int i = 0; i < returnSize3; i++) {
        printf("%d ", result3[i]); // Output: 1 -1
    }
    printf("\n");
    free(result3);


    int nums4[] = {9, 11};
    int numsSize4 = sizeof(nums4) / sizeof(nums4[0]);
    int k4 = 2;
    int returnSize4;
    int* result4 = maxSlidingWindow(nums4, numsSize4, k4, &returnSize4);
    for (int i = 0; i < returnSize4; i++) {
        printf("%d ", result4[i]); // Output: 11
    }
    printf("\n");
    free(result4);

    int nums5[] = {4, -2};
    int numsSize5 = sizeof(nums5) / sizeof(nums5[0]);
    int k5 = 2;
    int returnSize5;
    int* result5 = maxSlidingWindow(nums5, numsSize5, k5, &returnSize5);
    for (int i = 0; i < returnSize5; i++) {
        printf("%d ", result5[i]); // Output: 4
    }
    printf("\n");
    free(result5);



    return 0;
}