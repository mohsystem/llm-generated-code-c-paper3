#include <stdio.h>
#include <limits.h>

#define MAX 1000

typedef struct {
    int arr[MAX];
    int front, rear;
} Queue;

int isFull(Queue *queue) {
    return (queue->rear == MAX - 1);
}

int isEmpty(Queue *queue) {
    return (queue->front == -1);
}

void enqueue(Queue *queue, int item) {
    if (isFull(queue))
        return;

    if (queue->front == -1)
        queue->front = 0;

    queue->arr[++queue->rear] = item;
}

int dequeue(Queue *queue) {
    if (isEmpty(queue))
        return INT_MIN;

    int item = queue->arr[queue->front];

    if (queue->front >= queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front++;
    }

    return item;
}

int peek(Queue *queue) {
    if (isEmpty(queue))
        return INT_MIN;

    return queue->arr[queue->front];
}

int main() {
    Queue queue = {.front = -1, .rear = -1};
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    enqueue(&queue, 3);

    printf("%d\n", dequeue(&queue));
    printf("%d\n", peek(&queue));
    enqueue(&queue, 4);
    printf("%d\n", dequeue(&queue));
    printf("%d\n", dequeue(&queue));
    printf("%d\n", dequeue(&queue));

    return 0;
}