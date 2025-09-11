#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front;
    int rear;
} Queue;

void initialize(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX_SIZE - 1) {
        fprintf(stderr, "Queue is full\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->data[q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    int value = q->data[q->front];
    if (q->front == q->rear) {
        initialize(q);
    } else {
        q->front++;
    }
    return value;
}

int peek(Queue *q) {
    if (isEmpty(q)) {
        fprintf(stderr, "Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return q->data[q->front];
}

int main() {
    Queue queue;
    initialize(&queue);
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    printf("%d\n", dequeue(&queue)); // Output: 10
    printf("%d\n", peek(&queue));   // Output: 20
    dequeue(&queue);
    enqueue(&queue, 40);
    printf("%d\n", dequeue(&queue)); // Output: 30
    printf("%d\n", dequeue(&queue)); // Output: 40
    printf("%d\n", isEmpty(&queue)); // Output: 1 (true)
    return 0;
}