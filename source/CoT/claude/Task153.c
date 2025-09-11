
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define MAX_QUEUE_SIZE 100

typedef struct {
    int vertices;
    int** adjacencyMatrix;
} Task153;

typedef struct {
    int items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == MAX_QUEUE_SIZE - 1) return;
    
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    if (isEmpty(q)) return -1;
    
    int item = q->items[q->front];
    if (q->front >= q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

Task153* createGraph(int vertices) {
    if (vertices <= 0 || vertices > MAX_VERTICES) return NULL;
    
    Task153* graph = (Task153*)malloc(sizeof(Task153));
    if (!graph) return NULL;
    
    graph->vertices = vertices;
    graph->adjacencyMatrix = (int**)malloc(vertices * sizeof(int*));
    if (!graph->adjacencyMatrix) {
        free(graph);
        return NULL;
    }
    
    for (int i = 0; i < vertices; i++) {
        graph->adjacencyMatrix[i] = (int*)calloc(vertices, sizeof(int));
        if (!graph->adjacencyMatrix[i]) {
            for (int j = 0; j < i; j++) {
                free(graph->adjacencyMatrix[j]);
            }
            free(graph->adjacencyMatrix);
            free(graph);
            return NULL;
        }
    }
    
    return graph;
}

void addEdge(Task153* graph, int v, int w) {
    if (!graph || v < 0 || w < 0 || v >= graph->vertices || w >= graph->vertices) return;
    graph->adjacencyMatrix[v][w] = 1;
}

void bfs(Task153* graph, int startVertex, int* result, int* resultSize) {
    if (!graph || startVertex < 0 || startVertex >= graph->vertices) {
        *resultSize = 0;
        return;
    }
    
    bool* visited = (bool*)calloc(graph->vertices, sizeof(bool));
    if (!visited) return;
    
    Queue queue;
    initQueue(&queue);
    
    visited[startVertex] = true;
    enqueue(&queue, startVertex);
    
    *resultSize = 0;
    
    while (!isEmpty(&queue)) {
        int vertex = dequeue(&queue);
        result[(*resultSize)++] = vertex;
        
        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjacencyMatrix[vertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(&queue, i);
            }
        }
    }
    
    free(visited);
}

void freeGraph(Task153* graph) {
    if (!graph) return;
    
    for (int i = 0; i < graph->vertices; i++) {
        free(graph->adjacencyMatrix[i]);
    }
    free(graph->adjacencyMatrix);
    free(graph);
}

void printResult(int* result, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", result[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\\n");
}

int main() {
    int result[MAX_VERTICES];
    int resultSize;

    // Test Case 1: Simple graph
    Task153* g1 = createGraph(4);
    addEdge(g1, 0, 1);
    addEdge(g1, 0, 2);
    addEdge(g1, 1, 2);
    addEdge(g1, 2, 0);
    addEdge(g1, 2, 3);
    addEdge(g1, 3, 3);
    printf("Test 1: ");
    bfs(g1, 2, result, &resultSize);
    printResult(result, resultSize);
    freeGraph(g1);

    // Test Case 2: Linear graph
    Task153* g2 = createGraph(3);
    addEdge(g2, 0, 1);
    addEdge(g2, 1, 2);
    printf("Test 2: ");
    bfs(g2, 0, result, &resultSize);
    printResult(result, resultSize);
    freeGraph(g2);

    // Test Case 3: Disconnected graph
    Task153* g3 = createGraph(4);
    addEdge(g3, 0, 1);
    addEdge(g3, 2, 3);
    printf("Test 3: ");
    bfs(g3, 0, result, &resultSize);
    printResult(result, resultSize);
    freeGraph(g3);

    // Test Case 4: Single node
    Task153* g4 = createGraph(1);
    printf("Test 4: ");
    bfs(g4, 0, result, &resultSize);
    printResult(result, resultSize);
    freeGraph(g4);

    // Test Case 5: Empty graph
    Task153* g5 = createGraph(0);
    printf("Test 5: ");
    bfs(g5, 0, result, &resultSize);
    printResult(result, resultSize);
    freeGraph(g5);

    return 0;
}
