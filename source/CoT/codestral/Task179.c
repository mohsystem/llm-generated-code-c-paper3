#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (int*)malloc(sizeof(int) * capacity);
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void destroyQueue(Queue* queue) {
    free(queue->data);
    free(queue);
}

void push(Queue* queue, int value) {
    if (queue->size == queue->capacity) {
        queue->capacity *= 2;
        queue->data = (int*)realloc(queue->data, sizeof(int) * queue->capacity);
    }
    queue->data[queue->size++] = value;
}

void pop(Queue* queue) {
    if (queue->size > 0) {
        for (int i = 0; i < queue->size - 1; i++) {
            queue->data[i] = queue->data[i + 1];
        }
        queue->size--;
    }
}

int front(Queue* queue) {
    return queue->data[0];
}

int back(Queue* queue) {
    return queue->data[queue->size - 1];
}

int empty(Queue* queue) {
    return queue->size == 0;
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (nums == NULL || k <= 0) {
        *returnSize = 0;
        return NULL;
    }
    int n = numsSize;
    int* r = (int*)malloc(sizeof(int) * (n - k + 1));
    Queue* queue = createQueue(n);
    for (int i = 0; i < n; i++) {
        while (!empty(queue) && queue->data[0] < i - k + 1) {
            pop(queue);
        }
        while (!empty(queue) && nums[back(queue)] < nums[i]) {
            pop(queue);
        }
        push(queue, i);
        if (i >= k - 1) {
            r[i - k + 1] = nums[front(queue)];
        }
    }
    *returnSize = n - k + 1;
    destroyQueue(queue);
    return r;
}

int main() {
    int nums1[] = {1,3,-1,-3,5,3,6,7};
    int nums2[] = {1};
    int returnSize1, returnSize2;
    int* res1 = maxSlidingWindow(nums1, 8, 3, &returnSize1);
    int* res2 = maxSlidingWindow(nums2, 1, 1, &returnSize2);
    for (int i = 0; i < returnSize1; i++) {
        printf("%d ", res1[i]);
    }
    printf("\n");
    for (int i = 0; i < returnSize2; i++) {
        printf("%d ", res2[i]);
    }
    printf("\n");
    free(res1);
    free(res2);
    return 0;
}