#include <stdio.h>
#include <stdlib.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct {
    int* data;
    int size;
    int capacity;
} Deque;

Deque* createDeque(int capacity) {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->data = (int*)malloc(sizeof(int) * capacity);
    deque->size = 0;
    deque->capacity = capacity;
    return deque;
}

void destroyDeque(Deque* deque) {
    free(deque->data);
    free(deque);
}

void pushBack(Deque* deque, int value) {
    if (deque->size == deque->capacity) {
        deque->capacity *= 2;
        deque->data = (int*)realloc(deque->data, sizeof(int) * deque->capacity);
    }
    deque->data[deque->size++] = value;
}

void pushFront(Deque* deque, int value) {
    if (deque->size == deque->capacity) {
        deque->capacity *= 2;
        deque->data = (int*)realloc(deque->data, sizeof(int) * deque->capacity);
    }
    for (int i = deque->size; i > 0; i--) {
        deque->data[i] = deque->data[i - 1];
    }
    deque->data[0] = value;
    deque->size++;
}

int front(Deque* deque) {
    return deque->data[0];
}

int back(Deque* deque) {
    return deque->data[deque->size - 1];
}

void popFront(Deque* deque) {
    for (int i = 0; i < deque->size - 1; i++) {
        deque->data[i] = deque->data[i + 1];
    }
    deque->size--;
}

void popBack(Deque* deque) {
    deque->size--;
}

int isEmpty(Deque* deque) {
    return deque->size == 0;
}

int shortestSubarray(int* nums, int numsSize, int k) {
    int n = numsSize;
    int* preSum = (int*)malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n; i++) {
        preSum[i + 1] = preSum[i] + nums[i];
    }

    int res = n + 1;
    Deque* deque = createDeque(n + 1);
    for (int i = 0; i <= n; i++) {
        while (!isEmpty(deque) && preSum[i] - preSum[front(deque)] >= k) {
            res = MIN(res, i - front(deque));
            popFront(deque);
        }
        while (!isEmpty(deque) && preSum[i] <= preSum[back(deque)]) {
            popBack(deque);
        }
        pushBack(deque, i);
    }
    int result = res <= n ? res : -1;
    destroyDeque(deque);
    free(preSum);
    return result;
}

int main() {
    int nums1[] = {1};
    printf("%d\n", shortestSubarray(nums1, 1, 1)); // Output: 1
    int nums2[] = {1, 2};
    printf("%d\n", shortestSubarray(nums2, 2, 4)); // Output: -1
    int nums3[] = {2, -1, 2};
    printf("%d\n", shortestSubarray(nums3, 3, 3)); // Output: 3
    return 0;
}