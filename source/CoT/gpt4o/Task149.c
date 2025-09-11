#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct SecureQueue {
    Node* front;
    Node* rear;
} SecureQueue;

SecureQueue* createQueue() {
    SecureQueue* queue = (SecureQueue*)malloc(sizeof(SecureQueue));
    queue->front = queue->rear = NULL;
    return queue;
}

void enqueue(SecureQueue* queue, int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

int dequeue(SecureQueue* queue) {
    if (queue->front == NULL) {
        return -1; // Indicating empty queue
    }
    Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

int peek(SecureQueue* queue) {
    if (queue->front == NULL) {
        return -1; // Indicating empty queue
    }
    return queue->front->data;
}

bool isEmpty(SecureQueue* queue) {
    return queue->front == NULL;
}

int main() {
    SecureQueue* queue = createQueue();
    
    // Test case 1
    enqueue(queue, 10);
    printf("%d\n", peek(queue)); // Output: 10

    // Test case 2
    enqueue(queue, 20);
    printf("%d\n", dequeue(queue)); // Output: 10

    // Test case 3
    printf("%d\n", peek(queue)); // Output: 20

    // Test case 4
    printf("%d\n", dequeue(queue)); // Output: 20

    // Test case 5
    printf("%s\n", isEmpty(queue) ? "true" : "false"); // Output: true

    free(queue);
    return 0;
}