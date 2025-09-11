#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int* arr;
    int front, rear, size, capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->arr = (int*)malloc(sizeof(int) * capacity);
    q->front = q->rear = q->size = 0;
    q->capacity = capacity;
    return q;
}

void freeQueue(Queue* q) {
    free(q->arr);
    free(q);
}

int is_empty(Queue* q) {
    return q->size == 0;
}

int is_full(Queue* q) {
    return q->size == q->capacity;
}

void enqueue(Queue* q, int data) {
    if (is_full(q)) {
        printf("Queue is full\n");
        return;
    }
    if (is_empty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % q->capacity;
    }
    q->arr[q->rear] = data;
    q->size++;
}

int dequeue(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int data = q->arr[q->front];
    if (q->size == 1) {
        q->front = q->rear = 0;
    } else {
        q->front = (q->front + 1) % q->capacity;
    }
    q->size--;
    return data;
}

int peek(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->arr[q->front];
}

void display(Queue* q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return;
    }
    int temp = q->front;
    for (int i = 0; i < q->size; i++) {
        printf("%d ", q->arr[temp]);
        temp = (temp + 1) % q->capacity;
    }
    printf("\n");
}

int main() {
    Queue* q = createQueue(5);
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    enqueue(q, 5);
    display(q); // Output: 1 2 3 4 5
    printf("Peek: %d\n", peek(q)); // Output: Peek: 1
    printf("Dequeue: %d\n", dequeue(q)); // Output: Dequeue: 1
    display(q); // Output: 2 3 4 5
    freeQueue(q);
    return 0;
}