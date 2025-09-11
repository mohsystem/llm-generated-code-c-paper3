#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct DequeNode {
    int value;
    struct DequeNode* next;
    struct DequeNode* prev;
} DequeNode;

typedef struct Deque {
    DequeNode* front;
    DequeNode* rear;
} Deque;

Deque* createDeque() {
    Deque* d = (Deque*)malloc(sizeof(Deque));
    d->front = NULL;
    d->rear = NULL;
    return d;
}

void pushFront(Deque* d, int value) {
    DequeNode* node = (DequeNode*)malloc(sizeof(DequeNode));
    node->value = value;
    node->next = d->front;
    node->prev = NULL;
    if (d->front != NULL) {
        d->front->prev = node;
    } else {
        d->rear = node;
    }
    d->front = node;
}

void pushRear(Deque* d, int value) {
    DequeNode* node = (DequeNode*)malloc(sizeof(DequeNode));
    node->value = value;
    node->next = NULL;
    node->prev = d->rear;
    if (d->rear != NULL) {
        d->rear->next = node;
    } else {
        d->front = node;
    }
    d->rear = node;
}

int popFront(Deque* d) {
    if (d->front == NULL) return -1;
    int value = d->front->value;
    DequeNode* temp = d->front;
    d->front = d->front->next;
    if (d->front != NULL) {
        d->front->prev = NULL;
    } else {
        d->rear = NULL;
    }
    free(temp);
    return value;
}

int popRear(Deque* d) {
    if (d->rear == NULL) return -1;
    int value = d->rear->value;
    DequeNode* temp = d->rear;
    d->rear = d->rear->prev;
    if (d->rear != NULL) {
        d->rear->next = NULL;
    } else {
        d->front = NULL;
    }
    free(temp);
    return value;
}

int shortestSubarray(int* nums, int n, int k) {
    long long prefixSum[n + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    Deque* queue = createDeque();
    pushRear(queue, 0);
    int ans = INT_MAX;

    for (int i = 1; i <= n; i++) {
        while (queue->front != NULL && prefixSum[i] - prefixSum[queue->front->value] >= k) {
            ans = (ans < i - queue->front->value) ? ans : i - queue->front->value;
            popFront(queue);
        }
        while (queue->rear != NULL && prefixSum[i] <= prefixSum[queue->rear->value]) {
            popRear(queue);
        }
        pushRear(queue, i);
    }

    return ans == INT_MAX ? -1 : ans;
}

int main() {
    int testCases[][5] = {
        {1}, {1, 2}, {2, -1, 2}, {2, 1, 1, -4, 3, 1, -1, 2}, {-8, -8, -3, 8}
    };
    int ks[] = {1, 4, 3, 5, 5};
    int sizes[] = {1, 2, 3, 8, 4};
    for (int i = 0; i < 5; i++) {
        printf("Input: nums = [");
        for (int j = 0; j < sizes[i]; j++) {
            printf("%d", testCases[i][j]);
            if (j < sizes[i] - 1) printf(", ");
        }
        printf("], k = %d\n", ks[i]);
        printf("Output: %d\n", shortestSubarray(testCases[i], sizes[i], ks[i]));
    }
    return 0;
}