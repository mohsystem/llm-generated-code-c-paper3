
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int queue[MAX_SIZE];
    int front;
    int rear;
    int size;
} Task149;

void initialize(Task149* q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool isEmpty(Task149* q) {
    return q->size == 0;
}

void enqueue(Task149* q, int data) {
    if (q->size == MAX_SIZE) {
        printf("Queue is full\\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->queue[q->rear] = data;
    q->size++;
}

int dequeue(Task149* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\\n");
        return -1;
    }
    int data = q->queue[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return data;
}

int peek(Task149* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\\n");
        return -1;
    }
    return q->queue[q->front];
}

int main() {
    Task149 q;
    initialize(&q);
    
    // Test case 1: Basic enqueue and dequeue
    enqueue(&q, 1);
    enqueue(&q, 2);
    printf("%d\\n", dequeue(&q));  // Should print 1
    
    // Test case 2: Peek operation
    enqueue(&q, 3);
    printf("%d\\n", peek(&q));  // Should print 2
    
    // Test case 3: Multiple operations
    enqueue(&q, 4);
    enqueue(&q, 5);
    printf("%d\\n", dequeue(&q));  // Should print 2
    printf("%d\\n", dequeue(&q));  // Should print 3
    
    // Test case 4: Empty queue check
    dequeue(&q);
    dequeue(&q);
    printf("%d\\n", isEmpty(&q));  // Should print 1 (true)
    
    // Test case 5: Circular behavior
    for(int i = 1; i <= 5; i++) {
        enqueue(&q, i);
    }
    for(int i = 1; i <= 3; i++) {
        printf("%d\\n", dequeue(&q));  // Should print 1, 2, 3
    }
    
    return 0;
}
