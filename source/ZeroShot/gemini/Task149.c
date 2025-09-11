#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Define a structure for the queue node
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// Define a structure for the queue itself
typedef struct MyQueue {
    Node *front;
    Node *rear;
    size_t itemSize; // Stores the size of each item in the queue
} MyQueue;



// Create a new queue
MyQueue *createQueue(size_t itemSize) {
    MyQueue *queue = (MyQueue *)malloc(sizeof(MyQueue));
    if (queue == NULL) {
        return NULL; // Memory allocation failed
    }
    queue->front = NULL;
    queue->rear = NULL;
    queue->itemSize = itemSize;
    return queue;
}


// Enqueue an item
int enqueue(MyQueue *queue, const void *item) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0; // Memory allocation failed
    }

    newNode->data = malloc(queue->itemSize); // Allocate memory for the data
    if (newNode->data == NULL) {
        free(newNode);
        return 0; // Memory allocation failed
    }
    memcpy(newNode->data, item, queue->itemSize); // Copy the data
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    return 1; // Success
}

// Dequeue an item
void *dequeue(MyQueue *queue) {
    if (queue->front == NULL) {
        return NULL; // Queue is empty
    }

    Node *temp = queue->front;
    void *data = temp->data; // Get the data pointer before freeing the node

    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL; // Queue became empty
    }
    free(temp);
    return data;
}


// Peek at the front item
void *peek(MyQueue *queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    return queue->front->data;
}


// Check if the queue is empty
int isEmpty(MyQueue *queue) {
    return queue->front == NULL;
}

// Destroy the queue (free all allocated memory)
void destroyQueue(MyQueue *queue) {
    while (!isEmpty(queue)) {
        free(dequeue(queue));
    }
    free(queue);
}


int main() {
     // Test case 1 - Integers
    MyQueue *intQueue = createQueue(sizeof(int));
    int a = 1, b = 2, c = 3;

    enqueue(intQueue, &a);
    enqueue(intQueue, &b);
    enqueue(intQueue, &c);

    int *dequeuedInt = (int *)dequeue(intQueue);
    printf("Dequeued int: %d\n", *dequeuedInt); // Output: 1
    free(dequeuedInt); // Free the dequeued item

    int *peekedInt = (int *)peek(intQueue);
    printf("Peeked int: %d\n", *peekedInt); // Output: 2

    destroyQueue(intQueue);


    // Test case 2 - Strings (char arrays)
    MyQueue *stringQueue = createQueue(sizeof(char[20]));
    char str1[] = "apple";
    char str2[] = "banana";
    enqueue(stringQueue, str1);
    enqueue(stringQueue, str2);

    char *dequeuedStr1 = (char *)dequeue(stringQueue);
    printf("Dequeued string: %s\n", dequeuedStr1); // Output: apple
    free(dequeuedStr1);


    char *dequeuedStr2 = (char *)dequeue(stringQueue);
    printf("Dequeued string: %s\n", dequeuedStr2); // Output: banana
    free(dequeuedStr2);

    destroyQueue(stringQueue);

    // Test case 3 - Empty queue
    MyQueue *emptyQueue = createQueue(sizeof(double));
    if (dequeue(emptyQueue) == NULL) {
        printf("Queue is empty (dequeue test)\n"); // Correct output
    }

    destroyQueue(emptyQueue);

    // Test case 4 - Peek on empty queue
    MyQueue *emptyQueue2 = createQueue(sizeof(char));
    if (peek(emptyQueue2) == NULL) {
        printf("Queue is empty (peek test)\n"); // Correct output
    }
    destroyQueue(emptyQueue2);


    return 0;
}