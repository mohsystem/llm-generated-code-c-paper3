#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 5

typedef struct {
    int* items;
    int front, rear, size;
} Task149;

Task149* createQueue() {
    Task149* queue = (Task149*)malloc(sizeof(Task149));
    queue->items = (int*)malloc(CAPACITY * sizeof(int));
    queue->front = queue->rear = queue->size = 0;
    return queue;
}

void freeQueue(Task149* queue) {
    free(queue->items);
    free(queue);
}

int isFull(Task149* queue) {
    return queue->size == CAPACITY;
}

int isEmpty(Task149* queue) {
    return queue->size == 0;
}

void enqueue(Task149* queue, int element) {
    if (isFull(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->items[queue->rear] = element;
    queue->rear = (queue->rear + 1) % CAPACITY;
    queue->size++;
    printf("Inserted %d\n", element);
}

int dequeue(Task149* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int element = queue->items[queue->front];
    queue->front = (queue->front + 1) % CAPACITY;
    queue->size--;
    printf("%d Deleted\n", element);
    return element;
}

int peek(Task149* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    return queue->items[queue->front];
}

void display(Task149* queue) {
    if (isEmpty(queue)) {
        printf("Empty Queue\n");
        return;
    }
    int temp = queue->front;
    for (int i = 0; i < queue->size; i++) {
        printf("%d ", queue->items[temp]);
        temp = (temp + 1) % CAPACITY;
    }
    printf("\n");
}

int main() {
    Task149* queue = createQueue();
    dequeue(queue); // Queue is empty
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    enqueue(queue, 6); // Queue is full
    display(queue); // 1 2 3 4 5
    printf("Peek: %d\n", peek(queue)); // Peek: 1
    dequeue(queue);
    display(queue); // 2 3 4 5
    freeQueue(queue);
    return 0;
}