#include <stdio.h>
#include <stdlib.h>

#define QUEUE_CAPACITY 100

typedef struct {
    int items[QUEUE_CAPACITY];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
}

void enqueue(Queue* q, int item) {
    if (q->rear == QUEUE_CAPACITY - 1) {
        printf("Queue is full\n");
        return;
    }
    q->items[++q->rear] = item;
}

int dequeue(Queue* q) {
    if (q->front > q->rear) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return q->items[q->front++];
}

int peek(Queue* q) {
    if (q->front > q->rear) {
        printf("Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return q->items[q->front];
}

int main() {
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);

    printf("%d\n", dequeue(&queue)); // 10
    printf("%d\n", peek(&queue));    // 20
    enqueue(&queue, 40);
    printf("%d\n", dequeue(&queue)); // 20

    return 0;
}