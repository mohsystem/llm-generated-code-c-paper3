
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

bool enqueue(Task149* q, int element) {
    if (q->size >= MAX_SIZE) {
        return false;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->queue[q->rear] = element;
    q->size++;
    return true;
}

bool dequeue(Task149* q, int* element) {
    if (q->size == 0) {
        return false;
    }
    *element = q->queue[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return true;
}

bool peek(Task149* q, int* element) {
    if (q->size == 0) {
        return false;
    }
    *element = q->queue[q->front];
    return true;
}

bool isEmpty(Task149* q) {
    return q->size == 0;
}

int main() {
    Task149 queue;
    initialize(&queue);
    int element;
    
    // Test case 1: Basic enqueue and dequeue
    enqueue(&queue, 1);
    enqueue(&queue, 2);
    dequeue(&queue, &element);
    printf("%d\\n", element);  // Should print 1
    
    // Test case 2: Peek operation
    enqueue(&queue, 3);
    peek(&queue, &element);
    printf("%d\\n", element);  // Should print 2
    
    // Test case 3: Multiple operations
    enqueue(&queue, 4);
    dequeue(&queue, &element);
    printf("%d\\n", element);  // Should print 2
    dequeue(&queue, &element);
    printf("%d\\n", element);  // Should print 3
    
    // Test case 4: Empty queue check
    printf("%d\\n", isEmpty(&queue));  // Should print 0
    dequeue(&queue, &element);
    printf("%d\\n", isEmpty(&queue));  // Should print 1
    
    // Test case 5: Error handling
    if (!dequeue(&queue, &element)) {
        printf("Error: Queue is empty\\n");
    }
    
    return 0;
}
