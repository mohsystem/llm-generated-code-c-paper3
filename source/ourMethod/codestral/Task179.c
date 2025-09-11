#include <stdio.h>
#include <stdlib.h>

typedef struct Deque {
    int *data;
    int front, rear, size;
    unsigned capacity;
} Deque;

Deque* createDeque(unsigned capacity) {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->capacity = capacity;
    deque->front = deque->size = 0;
    deque->rear = capacity - 1;
    deque->data = (int*)malloc(deque->capacity * sizeof(int));
    return deque;
}

int isFull(Deque* deque) {
    return (deque->size == deque->capacity);
}

int isEmpty(Deque* deque) {
    return (deque->size == 0);
}

void addRear(Deque* deque, int item) {
    if (isFull(deque)) return;
    deque->rear = (deque->rear + 1) % deque->capacity;
    deque->data[deque->rear] = item;
    deque->size = deque->size + 1;
}

void addFront(Deque* deque, int item) {
    if (isFull(deque)) return;
    deque->front = (deque->front - 1 + deque->capacity) % deque->capacity;
    deque->data[deque->front] = item;
    deque->size = deque->size + 1;
}

int removeFront(Deque* deque) {
    if (isEmpty(deque)) return -1;
    int item = deque->data[deque->front];
    deque->front = (deque->front + 1) % deque->capacity;
    deque->size = deque->size - 1;
    return item;
}

int removeRear(Deque* deque) {
    if (isEmpty(deque)) return -1;
    int item = deque->data[deque->rear];
    deque->rear = (deque->rear - 1 + deque->capacity) % deque->capacity;
    deque->size = deque->size - 1;
    return item;
}

int getFront(Deque* deque) {
    if (isEmpty(deque)) return -1;
    return deque->data[deque->front];
}

int getRear(Deque* deque) {
    if (isEmpty(deque)) return -1;
    return deque->data[deque->rear];
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (nums == NULL || k <= 0) {
        *returnSize = 0;
        return NULL;
    }
    int n = numsSize;
    int* result = (int*)malloc((n - k + 1) * sizeof(int));
    Deque* deque = createDeque(n);
    for (int i = 0; i < n; i++) {
        while (!isEmpty(deque) && getFront(deque) < i - k + 1) {
            removeFront(deque);
        }
        while (!isEmpty(deque) && nums[getRear(deque)] < nums[i]) {
            removeRear(deque);
        }
        addRear(deque, i);
        if (i >= k - 1) {
            result[i - k + 1] = nums[getFront(deque)];
        }
    }
    *returnSize = n - k + 1;
    return result;
}

int main() {
    int nums1[] = {1,3,-1,-3,5,3,6,7};
    int nums2[] = {1};
    int returnSize1, returnSize2;
    int* res1 = maxSlidingWindow(nums1, 8, 3, &returnSize1);
    int* res2 = maxSlidingWindow(nums2, 1, 1, &returnSize2);
    for(int i = 0; i < returnSize1; i++) printf("%d ", res1[i]);
    printf("\n");
    for(int i = 0; i < returnSize2; i++) printf("%d ", res2[i]);
    return 0;
}