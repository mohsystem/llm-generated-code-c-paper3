#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void enqueue(Queue* queue, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

int dequeue(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        return -1;
    }

    int data = queue->front->data;
    Node* temp = queue->front;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return data;
}

void bfs(int** graph, int numVertices, int start) {
    bool* visited = (bool*)calloc(numVertices, sizeof(bool));
    Queue queue;
    queue.front = NULL;
    queue.rear = NULL;

    visited[start] = true;
    enqueue(&queue, start);

    while (queue.front != NULL) {
        int vertex = dequeue(&queue);
        printf("%d ", vertex);

        for (int i = 0; i < numVertices; i++) {
            if (graph[vertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(&queue, i);
            }
        }
    }

    free(visited);
}

int main() {
    int numVertices = 5;
    int** graph = (int**)malloc(numVertices * sizeof(int*));
    for (int i = 0; i < numVertices; i++) {
        graph[i] = (int*)malloc(numVertices * sizeof(int));
    }

    // Initialize graph
    graph[0][0] = 0; graph[0][1] = 1; graph[0][2] = 1; graph[0][3] = 0; graph[0][4] = 0;
    graph[1][0] = 1; graph[1][1] = 0; graph[1][2] = 0; graph[1][3] = 1; graph[1][4] = 1;
    graph[2][0] = 1; graph[2][1] = 0; graph[2][2] = 0; graph[2][3] = 1; graph[2][4] = 0;
    graph[3][0] = 0; graph[3][1] = 1; graph[3][2] = 1; graph[3][3] = 0; graph[3][4] = 1;
    graph[4][0] = 0; graph[4][1] = 1; graph[4][2] = 0; graph[4][3] = 1; graph[4][4] = 0;

    printf("BFS Traversal starting from vertex 0:\n");
    bfs(graph, numVertices, 0);
    printf("\n");

    printf("BFS Traversal starting from vertex 1:\n");
    bfs(graph, numVertices, 1);
    printf("\n");

    printf("BFS Traversal starting from vertex 2:\n");
    bfs(graph, numVertices, 2);
    printf("\n");

    printf("BFS Traversal starting from vertex 3:\n");
    bfs(graph, numVertices, 3);
    printf("\n");

    printf("BFS Traversal starting from vertex 4:\n");
    bfs(graph, numVertices, 4);
    printf("\n");

    // Free memory
    for (int i = 0; i < numVertices; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}