#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

typedef struct {
    int* queue;
    int front, rear, size;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->queue = (int*)malloc(sizeof(int) * capacity);
    q->front = q->rear = q->size = 0;
    return q;
}

void freeQueue(Queue* q) {
    free(q->queue);
    free(q);
}

int isFull(Queue* q) {
    return q->size == SIZE;
}

int isEmpty(Queue* q) {
    return q->size == 0;
}

void enqueue(Queue* q, int element) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    q->queue[q->rear] = element;
    q->rear = (q->rear + 1) % SIZE;
    q->size++;
    printf("Inserted %d\n", element);
}

int dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int element = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    q->size--;
    printf("%d Deleted\n", element);
    return element;
}

int peek(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->queue[q->front];
}

void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Empty Queue\n");
        return;
    }
    int i = q->front;
    for (int count = 0; count < q->size; count++) {
        printf("%d ", q->queue[i]);
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    Queue* q = createQueue(SIZE);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    display(q);
    dequeue(q);
    display(q);
    printf("Peek: %d\n", peek(q));
    freeQueue(q);
    return 0;
}