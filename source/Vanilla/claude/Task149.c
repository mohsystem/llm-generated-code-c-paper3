
#include <stdio.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int front;
    int rear;
    int size;
} Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

void enqueue(Queue* q, int data) {
    if (q->size == MAX_SIZE) {
        printf("Queue is full\\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->arr[q->rear] = data;
    q->size++;
}

int dequeue(Queue* q) {
    if (q->size == 0) {
        printf("Queue is empty\\n");
        return -1;
    }
    int data = q->arr[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return data;
}

int peek(Queue* q) {
    if (q->size == 0) {
        printf("Queue is empty\\n");
        return -1;
    }
    return q->arr[q->front];
}

int main() {
    // Test case 1: Basic enqueue and dequeue
    Queue queue;
    initQueue(&queue);
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    printf("%d\\n", dequeue(&queue));  // Should print 1
    
    // Test case 2: Peek operation
    enqueue(&queue, 3);
    printf("%d\\n", peek(&queue));  // Should print 2
    
    // Test case 3: Multiple operations
    enqueue(&queue, 4);
    enqueue(&queue, 5);
    printf("%d\\n", dequeue(&queue));  // Should print 2
    printf("%d\\n", dequeue(&queue));  // Should print 3
    
    // Test case 4: Empty queue operations
    Queue emptyQueue;
    initQueue(&emptyQueue);
    printf("%d\\n", dequeue(&emptyQueue));  // Should print "Queue is empty" and -1
    
    // Test case 5: Circular array behavior
    Queue q;
    initQueue(&q);
    for(int i = 1; i <= 5; i++) {
        enqueue(&q, i);
        dequeue(&q);
    }
    enqueue(&q, 10);
    printf("%d\\n", peek(&q));  // Should print 10
    
    return 0;
}
