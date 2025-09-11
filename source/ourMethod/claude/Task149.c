
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int* array;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    if (capacity <= 0) {
        fprintf(stderr, "Error: Capacity must be positive\\n");
        return NULL;
    }
    
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (!queue) {
        fprintf(stderr, "Error: Memory allocation failed\\n");
        return NULL;
    }
    
    queue->array = (int*)malloc(capacity * sizeof(int));
    if (!queue->array) {
        fprintf(stderr, "Error: Memory allocation failed\\n");
        free(queue);
        return NULL;
    }
    
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    return queue;
}

bool enqueue(Queue* queue, int value) {
    if (!queue) {
        return false;
    }
    
    if (queue->size >= queue->capacity) {
        return false;
    }
    
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = value;
    queue->size++;
    return true;
}

bool dequeue(Queue* queue, int* value) {
    if (!queue || !value) {
        return false;
    }
    
    if (queue->size <= 0) {
        return false;
    }
    
    *value = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return true;
}

bool peek(Queue* queue, int* value) {
    if (!queue || !value) {
        return false;
    }
    
    if (queue->size <= 0) {
        return false;
    }
    
    *value = queue->array[queue->front];
    return true;
}

bool isEmpty(Queue* queue) {
    return !queue || queue->size == 0;
}

void destroyQueue(Queue* queue) {
    if (queue) {
        free(queue->array);
        free(queue);
    }
}

int main() {
    // Test case 1: Basic operations
    Queue* q1 = createQueue(5);
    if (q1) {
        enqueue(q1, 1);
        enqueue(q1, 2);
        int value;
        if (peek(q1, &value)) {
            printf("Peek: %d\\n", value);  // Should print 1
        }
        if (dequeue(q1, &value)) {
            printf("Dequeue: %d\\n", value);  // Should print 1
        }
        destroyQueue(q1);
    }
    
    // Test case 2: Empty queue
    Queue* q2 = createQueue(3);
    if (q2) {
        int value;
        if (!dequeue(q2, &value)) {
            printf("Test passed: Cannot dequeue from empty queue\\n");
        }
        destroyQueue(q2);
    }
    
    // Test case 3: Full queue
    Queue* q3 = createQueue(2);
    if (q3) {
        enqueue(q3, 1);
        enqueue(q3, 2);
        if (!enqueue(q3, 3)) {
            printf("Test passed: Cannot enqueue to full queue\\n");
        }
        destroyQueue(q3);
    }
    
    // Test case 4: Circular behavior
    Queue* q4 = createQueue(3);
    if (q4) {
        enqueue(q4, 1);
        enqueue(q4, 2);
        enqueue(q4, 3);
        int value;
        dequeue(q4, &value);
        dequeue(q4, &value);
        enqueue(q4, 4);
        if (peek(q4, &value)) {
            printf("Peek after circular: %d\\n", value);  // Should print 3
        }
        destroyQueue(q4);
    }
    
    // Test case 5: Invalid capacity
    Queue* q5 = createQueue(-1);
    if (!q5) {
        printf("Test passed: Cannot create queue with negative capacity\\n");
    }
    
    return 0;
}
