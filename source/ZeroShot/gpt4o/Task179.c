#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
} Deque;

Deque* createDeque(int n) {
    Deque* deq = (Deque*)malloc(sizeof(Deque));
    deq->data = (int*)malloc(n * sizeof(int));
    deq->front = 0;
    deq->rear = 0;
    deq->size = 0;
    return deq;
}

void destroyDeque(Deque* deq) {
    free(deq->data);
    free(deq);
}

void pushBack(Deque* deq, int value, int n) {
    deq->data[deq->rear] = value;
    deq->rear = (deq->rear + 1) % n;
    deq->size++;
}

void popFront(Deque* deq, int n) {
    deq->front = (deq->front + 1) % n;
    deq->size--;
}

void popBack(Deque* deq, int n) {
    deq->rear = (deq->rear - 1 + n) % n;
    deq->size--;
}

int front(Deque* deq, int n) {
    return deq->data[deq->front];
}

int back(Deque* deq, int n) {
    return deq->data[(deq->rear - 1 + n) % n];
}

int isEmpty(Deque* deq) {
    return deq->size == 0;
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    Deque* deq = createDeque(numsSize);
    int ri = 0;

    for (int i = 0; i < numsSize; ++i) {
        if (!isEmpty(deq) && front(deq, numsSize) < i - k + 1) {
            popFront(deq, numsSize);
        }
        
        while (!isEmpty(deq) && nums[back(deq, numsSize)] < nums[i]) {
            popBack(deq, numsSize);
        }
        
        pushBack(deq, i, numsSize);
        
        if (i >= k - 1) {
            result[ri++] = nums[front(deq, numsSize)];
        }
    }
    destroyDeque(deq);
    return result;
}

int main() {
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int nums2[] = {1};
    int nums3[] = {1, -1};
    int nums4[] = {9, 11};
    int nums5[] = {4, -2};
    int returnSize;
    
    int* result1 = maxSlidingWindow(nums1, 8, 3, &returnSize);
    for (int i = 0; i < returnSize; i++) printf("%d ", result1[i]);
    printf("\n");
    free(result1);
    
    int* result2 = maxSlidingWindow(nums2, 1, 1, &returnSize);
    for (int i = 0; i < returnSize; i++) printf("%d ", result2[i]);
    printf("\n");
    free(result2);
    
    int* result3 = maxSlidingWindow(nums3, 2, 1, &returnSize);
    for (int i = 0; i < returnSize; i++) printf("%d ", result3[i]);
    printf("\n");
    free(result3);
    
    int* result4 = maxSlidingWindow(nums4, 2, 2, &returnSize);
    for (int i = 0; i < returnSize; i++) printf("%d ", result4[i]);
    printf("\n");
    free(result4);
    
    int* result5 = maxSlidingWindow(nums5, 2, 2, &returnSize);
    for (int i = 0; i < returnSize; i++) printf("%d ", result5[i]);
    printf("\n");
    free(result5);
    
    return 0;
}