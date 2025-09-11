#include <stdio.h>
#include <stdlib.h>

// Note: C does not have built-in generics.  This implementation is for integers.
// For other data types, a different queue implementation would be needed.

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} MyQueue;

MyQueue *createQueue() {
    MyQueue *q = (MyQueue *)malloc(sizeof(MyQueue));
    if (!q) return NULL;
    q->head = q->tail = NULL;
    return q;
}

void enqueue(MyQueue *q, int item) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) return; 
    newNode->data = item;
    newNode->next = NULL;

    if (q->tail == NULL) {
        q->head = q->tail = newNode;
    } else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

int dequeue(MyQueue *q) {
    if (q->head == NULL) {
        return -1; // Or handle the error differently
    }
    Node *temp = q->head;
    int data = temp->data;
    q->head = temp->next;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    free(temp);
    return data;
}

int peek(MyQueue *q) {
    if (q->head == NULL) {
        return -1; // Or handle the error differently
    }
    return q->head->data;
}


int isEmpty(MyQueue *q) {
    return q->head == NULL;
}


int main() {
    MyQueue *queue1 = createQueue();
    enqueue(queue1, 10);
    enqueue(queue1, 20);
    enqueue(queue1, 30);
    printf("Peek: %d\n", peek(queue1));
    printf("Dequeue: %d\n", dequeue(queue1));
    printf("Peek: %d\n", peek(queue1));

   // Demonstrating other test cases would require creating separate queue
   // implementations for different types (string, double, char), which is
   // more complex in C without generics.  The logic would be similar to 
   // the integer example.

    // Example of checking for empty queue:
    MyQueue *queue4 = createQueue();
    printf("Is queue4 empty? %d\n", isEmpty(queue4)); // Should be 1 (true)

    enqueue(queue4, 1);
    enqueue(queue4, 2);
    printf("Is queue4 empty? %d\n", isEmpty(queue4)); // Should be 0 (false)
    
    printf("Dequeue: %d\n", dequeue(queue4));
    printf("Dequeue: %d\n", dequeue(queue4));
    printf("Is queue4 empty? %d\n", isEmpty(queue4)); // Should be 1 (true)

    // Clean up allocated memory (important in C!)
    free(queue1);
    free(queue4);


    return 0;
}