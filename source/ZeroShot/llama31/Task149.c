#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* queue;
    int front;
    int rear;
    int size;
    int capacity;
} Task149;

Task149* createQueue(int capacity) {
    Task149* queue = (Task149*)malloc(sizeof(Task149));
    queue->queue = (int*)malloc(sizeof(int) * capacity);
    queue->front = -1;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

void freeQueue(Task149* queue) {
    free(queue->queue);
    free(queue);
}

void enqueue(Task149* queue, int element) {
    if (queue->size == queue->capacity) {
        printf("Queue is full. Cannot enqueue.\n");
        return;
    }
    if (queue->size == 0) {
        queue->front = 0;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->queue[queue->rear] = element;
    queue->size++;
}

int dequeue(Task149* queue) {
    if (queue->size == 0) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    }
    int element = queue->queue[queue->front];
    if (queue->size == 1) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }
    queue->size--;
    return element;
}

int peek(Task149* queue) {
    if (queue->size == 0) {
        printf("Queue is empty. Cannot peek.\n");
        return -1;
    }
    return queue->queue[queue->front];
}

int main() {
    Task149* queue = createQueue(5);
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    printf("Dequeued: %d\n", dequeue(queue)); // Output: Dequeued: 1
    printf("Peek: %d\n", peek(queue)); // Output: Peek: 2
    enqueue(queue, 4);
    enqueue(queue, 5);
    printf("Dequeued: %d\n", dequeue(queue)); // Output: Dequeued: 2
    printf("Peek: %d\n", peek(queue)); // Output: Peek: 3
    freeQueue(queue);
    return 0;
}