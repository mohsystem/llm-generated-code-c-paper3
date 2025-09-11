#include <stdio.h>
#include <stdlib.h>

// Structure to represent a deque node
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Structure to represent a deque
typedef struct Deque {
    Node* front;
    Node* rear;
} Deque;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to initialize the deque
void initDeque(Deque* d) {
    d->front = NULL;
    d->rear = NULL;
}

// Function to add an element to the front of the deque
void addFront(Deque* d, int data) {
    Node* newNode = createNode(data);
    if (d->front == NULL) {
        d->front = newNode;
        d->rear = newNode;
    } else {
        newNode->next = d->front;
        d->front->prev = newNode;
        d->front = newNode;
    }
}

// Function to add an element to the rear of the deque
void addRear(Deque* d, int data) {
    Node* newNode = createNode(data);
    if (d->rear == NULL) {
        d->front = newNode;
        d->rear = newNode;
    } else {
        newNode->prev = d->rear;
        d->rear->next = newNode;
        d->rear = newNode;
    }
}

// Function to remove an element from the front of the deque
void removeFront(Deque* d) {
    if (d->front == NULL) return;
    Node* temp = d->front;
    if (d->front == d->rear) {
        d->front = NULL;
        d->rear = NULL;
    } else {
        d->front = d->front->next;
        d->front->prev = NULL;
    }
    free(temp);
}

// Function to remove an element from the rear of the deque
void removeRear(Deque* d) {
    if (d->rear == NULL) return;
    Node* temp = d->rear;
    if (d->front == d->rear) {
        d->front = NULL;
        d->rear = NULL;
    } else {
        d->rear = d->rear->prev;
        d->rear->next = NULL;
    }
    free(temp);
}

// Function to get the maximum element in the current window
int* maxSlidingWindow(int* nums, int n, int k) {
    if (n == 0) return NULL;
    int* result = (int*)malloc((n - k + 1) * sizeof(int));
    int ri = 0;

    Deque d;
    initDeque(&d);

    for (int i = 0; i < n; i++) {
        // Remove elements from the back of the deque that are out of the current window
        while (d.front != NULL && d.front->data < i - k + 1) {
            removeFront(&d);
        }

        // Remove elements from the front of the deque that are smaller than the current element
        while (d.rear != NULL && nums[d.rear->data] < nums[i]) {
            removeRear(&d);
        }

        addRear(&d, i);

        // Add the maximum element of the current window to the result
        if (i >= k - 1) {
            result[ri++] = nums[d.front->data];
        }
    }

    return result;
}

int main() {
    // Test cases
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    int n1 = sizeof(nums1) / sizeof(nums1[0]);
    int* result1 = maxSlidingWindow(nums1, n1, k1);
    for (int i = 0; i < n1 - k1 + 1; i++) {
        printf("%d ", result1[i]);
    }
    printf("\n");
    free(result1);

    int nums2[] = {1};
    int k2 = 1;
    int n2 = sizeof(nums2) / sizeof(nums2[0]);
    int* result2 = maxSlidingWindow(nums2, n2, k2);
    for (int i = 0; i < n2 - k2 + 1; i++) {
        printf("%d ", result2[i]);
    }
    printf("\n");
    free(result2);

    int nums3[] = {1, 2, 3, 4, 5};
    int k3 = 2;
    int n3 = sizeof(nums3) / sizeof(nums3[0]);
    int* result3 = maxSlidingWindow(nums3, n3, k3);
    for (int i = 0; i < n3 - k3 + 1; i++) {
        printf("%d ", result3[i]);
    }
    printf("\n");
    free(result3);

    int nums4[] = {5, 4, 3, 2, 1};
    int k4 = 3;
    int n4 = sizeof(nums4) / sizeof(nums4[0]);
    int* result4 = maxSlidingWindow(nums4, n4, k4);
    for (int i = 0; i < n4 - k4 + 1; i++) {
        printf("%d ", result4[i]);
    }
    printf("\n");
    free(result4);

    int nums5[] = {1, 1, 1, 1, 1};
    int k5 = 2;
    int n5 = sizeof(nums5) / sizeof(nums5[0]);
    int* result5 = maxSlidingWindow(nums5, n5, k5);
    for (int i = 0; i < n5 - k5 + 1; i++) {
        printf("%d ", result5[i]);
    }
    printf("\n");
    free(result5);

    return 0;
}