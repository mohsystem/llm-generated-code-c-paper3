#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
    int capacity;
} Deque;

Deque* createDeque(int capacity) {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->data = (int*)malloc(sizeof(int) * capacity);
    deque->front = -1;
    deque->rear = -1;
    deque->size = 0;
    deque->capacity = capacity;
    return deque;
}

void pushBack(Deque* deque, int value) {
    if (deque->rear == deque->capacity - 1) {
        return;
    }

    if (deque->front == -1) {
        deque->front = 0;
    }

    deque->rear++;
    deque->data[deque->rear] = value;
    deque->size++;
}

void pushFront(Deque* deque, int value) {
    if (deque->front == 0) {
        return;
    }

    if (deque->front == -1) {
        deque->front = deque->rear = 0;
    } else {
        deque->front--;
    }

    deque->data[deque->front] = value;
    deque->size++;
}

void popFront(Deque* deque) {
    if (deque->front == -1) {
        return;
    }

    if (deque->front == deque->rear) {
        deque->front = deque->rear = -1;
    } else {
        deque->front++;
    }

    deque->size--;
}

void popBack(Deque* deque) {
    if (deque->front == -1) {
        return;
    }

    if (deque->front == deque->rear) {
        deque->front = deque->rear = -1;
    } else {
        deque->rear--;
    }

    deque->size--;
}

int front(Deque* deque) {
    if (deque->front == -1) {
        return -1;
    }

    return deque->data[deque->front];
}

int back(Deque* deque) {
    if (deque->front == -1) {
        return -1;
    }

    return deque->data[deque->rear];
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k <= 0) {
        *returnSize = 0;
        return NULL;
    }

    int n = numsSize;
    int* result = (int*)malloc(sizeof(int) * (n - k + 1));
    Deque* deque = createDeque(n);

    for (int i = 0; i < n; i++) {
        while (front(deque) != -1 && front(deque) < i - k + 1) {
            popFront(deque);
        }

        while (back(deque) != -1 && nums[back(deque)] < nums[i]) {
            popBack(deque);
        }

        pushBack(deque, i);

        if (i >= k - 1) {
            result[i - k + 1] = nums[front(deque)];
        }
    }

    *returnSize = n - k + 1;
    return result;
}

int main() {
    int nums1[] = {1,3,-1,-3,5,3,6,7};
    int returnSize1;
    int* result1 = maxSlidingWindow(nums1, 8, 3, &returnSize1);
    for (int i = 0; i < returnSize1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");

    int nums2[] = {1};
    int returnSize2;
    int* result2 = maxSlidingWindow(nums2, 1, 1, &returnSize2);
    for (int i = 0; i < returnSize2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");

    return 0;
}