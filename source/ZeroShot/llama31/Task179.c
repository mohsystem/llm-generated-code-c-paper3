#include <stdio.h>
#include <stdlib.h>

// Structure for a deque node
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Structure for the deque
typedef struct Deque {
    Node* front;
    Node* rear;
} Deque;

// Function to create a new deque node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to initialize the deque
void initDeque(Deque* d) {
    d->front = d->rear = NULL;
}

// Function to add an element to the rear of the deque
void pushRear(Deque* d, int data) {
    Node* newNode = createNode(data);
    if (d->rear == NULL) {
        d->front = d->rear = newNode;
    } else {
        d->rear->next = newNode;
        newNode->prev = d->rear;
        d->rear = newNode;
    }
}

// Function to remove an element from the front of the deque
void popFront(Deque* d) {
    if (d->front == NULL) return;
    Node* temp = d->front;
    if (d->front == d->rear) {
        d->front = d->rear = NULL;
    } else {
        d->front = d->front->next;
        d->front->prev = NULL;
    }
    free(temp);
}

// Function to remove an element from the rear of the deque
void popRear(Deque* d) {
    if (d->rear == NULL) return;
    Node* temp = d->rear;
    if (d->front == d->rear) {
        d->front = d->rear = NULL;
    } else {
        d->rear = d->rear->prev;
        d->rear->next = NULL;
    }
    free(temp);
}

// Function to get the maximum element in the sliding window
int* maxSlidingWindow(int* nums, int n, int k, int* resultLen) {
    Deque d;
    initDeque(&d);
    int* result = (int*)malloc((n - k + 1) * sizeof(int));
    *resultLen = 0;

    for (int i = 0; i < n; i++) {
        // Remove elements from the rear that are smaller than the current element
        while (d.rear != NULL && nums[d.rear->data] < nums[i]) {
            popRear(&d);
        }
        // Add the current element to the rear
        pushRear(&d, i);

        // If the front element is out of the window, remove it
        if (d.front->data <= i - k) {
            popFront(&d);
        }

        // Add the maximum element of the current window to the result
        if (i >= k - 1) {
            result[(*resultLen)++] = nums[d.front->data];
        }
    }

    return result;
}

int main() {
    // Test cases
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    int n1 = sizeof(nums1) / sizeof(nums1[0]);
    int resultLen1;
    int* result1 = maxSlidingWindow(nums1, n1, k1, &resultLen1);
    for (int i = 0; i < resultLen1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");

    int nums2[] = {1};
    int k2 = 1;
    int n2 = sizeof(nums2) / sizeof(nums2[0]);
    int resultLen2;
    int* result2 = maxSlidingWindow(nums2, n2, k2, &resultLen2);
    for (int i = 0; i < resultLen2; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");

    int nums3[] = {1, 2, 3, 4, 5};
    int k3 = 3;
    int n3 = sizeof(nums3) / sizeof(nums3[0]);
    int resultLen3;
    int* result3 = maxSlidingWindow(nums3, n3, k3, &resultLen3);
    for (int i = 0; i < resultLen3; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n");

    int nums4[] = {5, 4, 3, 2, 1};
    int k4 = 3;
    int n4 = sizeof(nums4) / sizeof(nums4[0]);
    int resultLen4;
    int* result4 = maxSlidingWindow(nums4, n4, k4, &resultLen4);
    for (int i = 0; i < resultLen4; i++) {
        printf("%d ", result4[i]);
    }
    printf("\n");

    int nums5[] = {1, 1, 1, 1, 1};
    int k5 = 3;
    int n5 = sizeof(nums5) / sizeof(nums5[0]);
    int resultLen5;
    int* result5 = maxSlidingWindow(nums5, n5, k5, &resultLen5);
    for (int i = 0; i < resultLen5; i++) {
        printf("%d ", result5[i]);
    }
    printf("\n");

    return 0;
}