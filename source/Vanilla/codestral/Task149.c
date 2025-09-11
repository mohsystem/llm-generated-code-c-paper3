#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Task149 {
    Node* front;
    Node* rear;
} Task149;

void enqueue(Task149* queue, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(Task149* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        exit(1);
    }

    int data = queue->front->data;
    Node* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

int peek(Task149* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        exit(1);
    }

    return queue->front->data;
}

int main() {
    Task149 queue = { .front = NULL, .rear = NULL };

    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);

    printf("%d\n", dequeue(&queue)); // 1
    printf("%d\n", peek(&queue)); // 2

    enqueue(&queue, 4);

    printf("%d\n", dequeue(&queue)); // 2
    printf("%d\n", dequeue(&queue)); // 3
    printf("%d\n", dequeue(&queue)); // 4

    return 0;
}