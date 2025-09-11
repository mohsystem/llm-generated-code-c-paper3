#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Define the structure for a queue node
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

// Define the queue structure
typedef struct {
    Node *front;
    Node *rear;
    int size;
    size_t elementSize; // Store the size of each element
} Queue;


// Function to create a new queue
Queue *createQueue(size_t elementSize) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    if (!q) {
        perror("Failed to allocate memory for queue");
        exit(EXIT_FAILURE);
    }
    q->front = q->rear = NULL;
    q->size = 0;
    q->elementSize = elementSize; // Initialize element size
    return q;
}

// Function to check if the queue is empty
bool isEmpty(Queue *q) {
    return q->size == 0;
}

// Function to enqueue an element
void enqueue(Queue *q, void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }

    newNode->data = malloc(q->elementSize); // Allocate memory for data
    if (!newNode->data) {
        perror("Failed to allocate memory for node data");
        exit(EXIT_FAILURE);
    }
    memcpy(newNode->data, data, q->elementSize); // Copy the data


    newNode->next = NULL;
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}


// Function to dequeue an element
void *dequeue(Queue *q) {
    if (isEmpty(q)) {
        return NULL;
    }
    Node *temp = q->front;
    void *data = temp->data; // Get the data pointer

    q->front = temp->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp); // Free only the node, not the data
    q->size--;
    return data; // Return the data pointer
}


// Function to peek at the front element
void *peek(Queue *q) {
    if (isEmpty(q)) {
        return NULL;
    }
    return q->front->data;
}



int main() {
    Queue *intQueue = createQueue(sizeof(int));

    int values[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        enqueue(intQueue, &values[i]);
    }

    int *dequeuedValue = (int *)dequeue(intQueue);
    if (dequeuedValue != NULL) {
        printf("%d\n", *dequeuedValue); // Output: 1
        free(dequeuedValue); // Free the memory allocated for the dequeued integer

    }


    int *peekedValue = (int *)peek(intQueue);
    if (peekedValue != NULL) {
        printf("%d\n", *peekedValue); // Output: 2
    }



    dequeuedValue = (int *)dequeue(intQueue);
    if (dequeuedValue != NULL) {
        printf("%d\n", *dequeuedValue); // Output: 2
        free(dequeuedValue);

    }

    printf("%s\n", isEmpty(intQueue) ? "true" : "false");  // Output: false


    dequeuedValue = (int *)dequeue(intQueue);

    if (dequeuedValue != NULL) {
        printf("%d\n", *dequeuedValue); // Output: 3
        free(dequeuedValue);
    }
    printf("%s\n", isEmpty(intQueue) ? "true" : "false");  // Output: true


        // String queue example
    Queue *stringQueue = createQueue(sizeof(char) * 10); // Max string length 10 including \0
    char *strings[] = {"apple", "banana"};

    enqueue(stringQueue, strings[0]);
    enqueue(stringQueue, strings[1]);

    char *dequeuedString = (char *)dequeue(stringQueue);
    if (dequeuedString != NULL) {
        printf("%s\n", dequeuedString); // Output: apple
        free(dequeuedString);
    }


    // Freeing the Queues
    while (!isEmpty(intQueue)) {
        free(dequeue(intQueue));
    }
    free(intQueue);

    while (!isEmpty(stringQueue)) {
        free(dequeue(stringQueue));
    }
    free(stringQueue);

    return 0;
}