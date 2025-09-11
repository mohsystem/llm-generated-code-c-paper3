#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* elements;
    int front, rear, size, capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->elements = (int*)malloc(queue->capacity * sizeof(int));
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    return queue;
}

void destroyQueue(Queue* queue) {
    free(queue->elements);
    free(queue);
}

int isFull(Queue* queue) {
    return queue->size == queue->capacity;
}

int isEmpty(Queue* queue) {
    return queue->size == 0;
}

void enqueue(Queue* queue, int item) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->elements[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return INT_MIN;
    }
    int item = queue->elements[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

int peek(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return INT_MIN;
    }
    return queue->elements[queue->front];
}

int main() {
    Queue* queue = createQueue(5);

    // Test cases
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 50);
    printf("Peek: %d\n", peek(queue));
    printf("Dequeue: %d\n", dequeue(queue));
    printf("Dequeue: %d\n", dequeue(queue));
    enqueue(queue, 60);
    printf("Peek: %d\n", peek(queue));
    printf("Dequeue: %d\n", dequeue(queue));

    destroyQueue(queue);
    return 0;
}