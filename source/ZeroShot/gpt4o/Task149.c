#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int front;
    int rear;
} Task149;

void initQueue(Task149* q) {
    q->front = 0;
    q->rear = 0;
}

void enqueue(Task149* q, int value) {
    if ((q->rear + 1) % MAX == q->front) {
        printf("Queue is full\n");
        return;
    }
    q->data[q->rear] = value;
    q->rear = (q->rear + 1) % MAX;
}

int dequeue(Task149* q) {
    if (q->front == q->rear) {
        printf("Queue is empty\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    return value;
}

int peek(Task149* q) {
    if (q->front == q->rear) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->data[q->front];
}

int main() {
    Task149 queue;
    initQueue(&queue);
    
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);
    
    printf("%d\n", dequeue(&queue)); // 1
    printf("%d\n", peek(&queue));    // 2
    printf("%d\n", dequeue(&queue)); // 2
    printf("%d\n", dequeue(&queue)); // 3
    printf("%d\n", dequeue(&queue)); // -1
    
    return 0;
}