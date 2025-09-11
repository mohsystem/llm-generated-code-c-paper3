#include <stdio.h>
#include <stdlib.h>

// Structure for a deque node
typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

// Structure for a deque
typedef struct Deque {
    Node *front;
    Node *rear;
} Deque;


// Function to create a new deque node
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}


// Function to create an empty deque
Deque* createDeque() {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->front = dq->rear = NULL;
    return dq;
}

// Function to check if the deque is empty
int isEmpty(Deque* dq) {
    return dq->front == NULL;
}

// Function to insert an element at the rear of the deque
void insertRear(Deque* dq, int data) {
    Node* node = newNode(data);
    if (isEmpty(dq)) {
        dq->front = dq->rear = node;
        return;
    }
    dq->rear->next = node;
    node->prev = dq->rear;
    dq->rear = node;
}

// Function to remove and return the front element of the deque
int removeFront(Deque* dq) {
    if (isEmpty(dq)) {
        return -1; // Or handle the error appropriately
    }
    Node* temp = dq->front;
    int data = temp->data;
    dq->front = temp->next;
    if (dq->front == NULL) {
        dq->rear = NULL;
    } else {
        dq->front->prev = NULL;
    }
    free(temp);
    return data;
}

// Function to remove and return the rear element of the deque
int removeRear(Deque* dq) {
    if (isEmpty(dq)) {
        return -1; // Or handle the error appropriately
    }
    Node *temp = dq->rear;
    int data = temp->data;
    dq->rear = temp->prev;

    if (dq->rear == NULL) {
        dq->front = NULL;
    } else {
        dq->rear->next = NULL;
    }
    free(temp);
    return data;
}

// Function to get the front element of the deque
int getFront(Deque *dq) {
    if (isEmpty(dq)) {
        return -1; // Or handle appropriately
    }
    return dq->front->data;
}



int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k <= 0) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc(sizeof(int) * (numsSize - k + 1));
    *returnSize = numsSize - k + 1;

    Deque* dq = createDeque();

    for (int i = 0; i < numsSize; i++) {
        while (!isEmpty(dq) && getFront(dq) < i - k + 1) {
            removeFront(dq);
        }
        while (!isEmpty(dq) && nums[getFront(dq)] < nums[i]) {
            removeRear(dq);
        }
        insertRear(dq, i);

        if (i >= k - 1) {
            result[i - k + 1] = nums[getFront(dq)];
        }

    }
     // Free the deque memory
    while(!isEmpty(dq)){
        removeFront(dq);
    }
    free(dq);
    return result;

}

int main() {
    int nums1[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int k1 = 3;
    int returnSize1;
    int* result1 = maxSlidingWindow(nums1, 8, k1, &returnSize1);
    for (int i = 0; i < returnSize1; i++) printf("%d ", result1[i]); // Output: 3 3 5 5 6 7
    printf("\n");
    free(result1);

    int nums2[] = {1};
    int k2 = 1;
    int returnSize2;
    int* result2 = maxSlidingWindow(nums2, 1, k2, &returnSize2);
    for (int i = 0; i < returnSize2; i++) printf("%d ", result2[i]); // Output: 1
    printf("\n");
    free(result2);

     int nums3[] = {1, -1};
    int k3 = 1;
    int returnSize3;
    int* result3 = maxSlidingWindow(nums3, 2, k3, &returnSize3);
    for (int i = 0; i < returnSize3; i++) printf("%d ", result3[i]); // Output: 1 -1
    printf("\n");
    free(result3);

    int nums4[] = {9, 11};
    int k4 = 2;
    int returnSize4;
    int* result4 = maxSlidingWindow(nums4, 2, k4, &returnSize4);
    for (int i = 0; i < returnSize4; i++) printf("%d ", result4[i]); // Output: 11
    printf("\n");
    free(result4);


    int nums5[] = {4, -2};
    int k5 = 2;
    int returnSize5;
    int* result5 = maxSlidingWindow(nums5, 2, k5, &returnSize5);
    for (int i = 0; i < returnSize5; i++) printf("%d ", result5[i]); // Output: 4
    printf("\n");
    free(result5);

    return 0;
}