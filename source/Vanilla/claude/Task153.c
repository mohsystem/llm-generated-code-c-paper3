
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

struct Queue {
    int items[MAX_VERTICES];
    int front;
    int rear;
};

struct Graph {
    int vertices;
    int** adjMatrix;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

void enqueue(struct Queue* q, int value) {
    if (q->rear == MAX_VERTICES - 1)
        return;
    if (q->front == -1)
        q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(struct Queue* q) {
    if (q->front == -1)
        return -1;
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    
    graph->adjMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adjMatrix[i] = (int*)calloc(vertices, sizeof(int));
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    graph->adjMatrix[src][dest] = 1;
}

void BFS(struct Graph* graph, int startVertex) {
    bool* visited = (bool*)calloc(graph->vertices, sizeof(bool));
    struct Queue* q = createQueue();
    
    visited[startVertex] = true;
    enqueue(q, startVertex);
    
    printf("%d ", startVertex);
    
    while (q->front != -1) {
        int currentVertex = dequeue(q);
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(q, i);
                printf("%d ", i);
            }
        }
    }
    printf("\\n");
    
    free(visited);
    free(q);
}

int main() {
    // Test Case 1
    struct Graph* g1 = createGraph(4);
    addEdge(g1, 0, 1);
    addEdge(g1, 0, 2);
    addEdge(g1, 1, 2);
    addEdge(g1, 2, 0);
    addEdge(g1, 2, 3);
    addEdge(g1, 3, 3);
    printf("Test 1: ");
    BFS(g1, 2);

    // Test Case 2
    struct Graph* g2 = createGraph(3);
    addEdge(g2, 0, 1);
    addEdge(g2, 1, 2);
    printf("Test 2: ");
    BFS(g2, 0);

    // Test Case 3
    struct Graph* g3 = createGraph(5);
    addEdge(g3, 0, 1);
    addEdge(g3, 0, 2);
    addEdge(g3, 1, 3);
    addEdge(g3, 2, 4);
    printf("Test 3: ");
    BFS(g3, 0);

    // Test Case 4
    struct Graph* g4 = createGraph(4);
    addEdge(g4, 0, 1);
    addEdge(g4, 1, 2);
    addEdge(g4, 2, 3);
    addEdge(g4, 3, 0);
    printf("Test 4: ");
    BFS(g4, 0);

    // Test Case 5
    struct Graph* g5 = createGraph(1);
    printf("Test 5: ");
    BFS(g5, 0);

    return 0;
}
