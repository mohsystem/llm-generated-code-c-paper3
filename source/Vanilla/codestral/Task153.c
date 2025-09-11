#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTICES 50

struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
};

struct Queue* createQueue();
void enqueue(struct Queue* q, int);
int dequeue(struct Queue* q);
void display(struct Queue q);
int isEmpty(struct Queue q);
void printBFS(int G[][7], int start, int n);

struct Queue* createQueue() {
    struct Queue* q = malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct Queue q) {
    if(q.rear == -1)
        return 1;
    else
        return 0;
}

void enqueue(struct Queue* q, int value){
    if(q->rear == MAX_VERTICES-1)
        printf("\nQueue is Full!!");
    else {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(struct Queue* q){
    int item;
    if(isEmpty(*q)) {
        printf("Queue is empty");
        item = -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear) {
            printf("Resetting queue ");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printBFS(int G[][7], int start, int n) {
    int i, j;
    int visited[7];
    struct Queue* q = createQueue();

    for(i = 0; i < n; i++)
        visited[i] = 0;

    printf("BFS Traversal: ");

    visited[start] = 1;
    enqueue(q, start);

    while(!isEmpty(*q)) {
        int currentVertex = dequeue(q);
        printf(" %d ", currentVertex);

        for(j = 0; j < n; j++) {
            if(G[currentVertex][j] == 1 && visited[j] == 0) {
                visited[j] = 1;
                enqueue(q, j);
            }
        }
    }
}

int main() {
    int G[7][7] = {
        {0, 1, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0},
        {0, 0, 1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 1, 0, 0}
    };

    printBFS(G, 0, 7);

    return 0;
}