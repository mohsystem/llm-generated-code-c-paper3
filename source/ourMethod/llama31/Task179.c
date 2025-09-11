#include <stdio.h>
#include <stdlib.h>

// Structure to represent a deque node
typedef struct Node {
    int value;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new deque node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        return NULL;
    }
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to initialize the deque
void initDeque(Node** front, Node** rear) {
    *front = NULL;
    *rear = NULL;
}

// Function to add an element to the front of the deque
void pushFront(Node** front, Node** rear, int value) {
    Node* newNode = createNode(value);
    if (*front == NULL) {
        *front = newNode;
        *rear = newNode;
    } else {
        newNode->next = *front;
        (*front)->prev = newNode;
        *front = newNode;
    }
}

// Function to add an element to the rear of the deque
void pushRear(Node** front, Node** rear, int value) {
    Node* newNode = createNode(value);
    if (*rear == NULL) {
        *front = newNode;
        *rear = newNode;
    } else {
        newNode->prev = *rear;
        (*rear)->next = newNode;
        *rear = newNode;
    }
}

// Function to remove an element from the front of the deque
void popFront(Node** front, Node** rear) {
    if (*front == NULL) {
        return;
    }
    Node* temp = *front;
    *front = (*front)->next;
    if (*front == NULL) {
        *rear = NULL;
    } else {
        (*front)->prev = NULL;
    }
    free(temp);
}

// Function to remove an element from the rear of the deque
void popRear(Node** front, Node** rear) {
    if (*rear == NULL) {
        return;
    }
    Node* temp = *rear;
    *rear = (*rear)->prev;
    if (*rear == NULL) {
        *front = NULL;
    } else {
        (*rear)->next = NULL;
    }
    free(temp);
}

// Function to get the maximum sliding window
int* maxSlidingWindow(int* nums, int numsSize, int k) {
    if (nums == NULL || numsSize == 0 || k == 0) {
        return NULL;
    }
    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    Node* front = NULL;
    Node* rear = NULL;
    initDeque(&front, &rear);

    for (int i = 0; i < numsSize; i++) {
        // Remove elements from the front of the deque that are out of the current window
        while (front != NULL && front->value < i - k + 1) {
            popFront(&front, &rear);
        }
        // Remove elements from the rear of the deque that are smaller than the current element
        while (rear != NULL && nums[rear->value] < nums[i]) {
            popRear(&front, &rear);
        }
        // Add the current element to the rear of the deque
        pushRear(&front, &rear, i);

        // Add the maximum element of the current window to the result
        if (i >= k - 1) {
            result[i - k + 1] = nums[front->value];
        }
    }
    return result;
}

int main() {
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int* result = maxSlidingWindow(nums, numsSize, k);
    for (int i = 0; i < numsSize - k + 1; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    int nums2[] = {1};
    k = 1;
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]);
    result = maxSlidingWindow(nums2, numsSize2, k);
    for (int i = 0; i < numsSize2 - k + 1; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}