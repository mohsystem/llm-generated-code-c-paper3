
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 1000

// Queue implementation
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isQueueEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, int item) {
    if (queue->size == queue->capacity)
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Graph implementation
struct Graph {
    int V;
    int** adj;
};

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    
    graph->adj = (int**)malloc(V * sizeof(int*));
    for(int i = 0; i < V; i++) {
        graph->adj[i] = (int*)calloc(V, sizeof(int));
    }
    return graph;
}

void addEdge(struct Graph* graph, int v, int w) {
    graph->adj[v][w] = 1;
}

void BFS(struct Graph* graph, int start, int* result, int* resultSize) {
    bool* visited = (bool*)calloc(graph->V, sizeof(bool));
    struct Queue* queue = createQueue(graph->V);
    
    visited[start] = true;
    enqueue(queue, start);
    
    *resultSize = 0;
    while (!isQueueEmpty(queue)) {
        int s = dequeue(queue);
        result[(*resultSize)++] = s;
        
        for (int i = 0; i < graph->V; i++) {
            if (graph->adj[s][i] && !visited[i]) {
                visited[i] = true;
                enqueue(queue, i);
            }
        }
    }
    
    free(visited);
    free(queue->array);
    free(queue);
}

void freeGraph(struct Graph* graph) {
    for(int i = 0; i < graph->V; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph);
}

int main() {
    int result[MAX_VERTICES];
    int resultSize;
    
    // Test Case 1: Simple graph with 4 nodes
    struct Graph* g1 = createGraph(4);
    addEdge(g1, 0, 1);
    addEdge(g1, 0, 2);
    addEdge(g1, 1, 2);
    addEdge(g1, 2, 0);
    addEdge(g1, 2, 3);
    addEdge(g1, 3, 3);
    printf("Test 1: ");
    BFS(g1, 2, result, &resultSize);
    for(int i = 0; i < resultSize; i++) printf("%d ", result[i]);
    printf("\\n");
    freeGraph(g1);
    
    // Test Case 2: Linear graph
    struct Graph* g2 = createGraph(5);
    addEdge(g2, 0, 1);
    addEdge(g2, 1, 2);
    addEdge(g2, 2, 3);
    addEdge(g2, 3, 4);
    printf("Test 2: ");
    BFS(g2, 0, result, &resultSize);
    for(int i = 0; i < resultSize; i++) printf("%d ", result[i]);
    printf("\\n");
    freeGraph(g2);
    
    // Test Case 3: Disconnected graph
    struct Graph* g3 = createGraph(7);
    addEdge(g3, 0, 1);
    addEdge(g3, 2, 3);
    addEdge(g3, 4, 5);
    addEdge(g3, 5, 6);
    printf("Test 3: ");
    BFS(g3, 4, result, &resultSize);
    for(int i = 0; i < resultSize; i++) printf("%d ", result[i]);
    printf("\\n");
    freeGraph(g3);
    
    // Test Case 4: Cyclic graph
    struct Graph* g4 = createGraph(4);
    addEdge(g4, 0, 1);
    addEdge(g4, 1, 2);
    addEdge(g4, 2, 3);
    addEdge(g4, 3, 0);
    printf("Test 4: ");
    BFS(g4, 0, result, &resultSize);
    for(int i = 0; i < resultSize; i++) printf("%d ", result[i]);
    printf("\\n");
    freeGraph(g4);
    
    // Test Case 5: Single node
    struct Graph* g5 = createGraph(1);
    printf("Test 5: ");
    BFS(g5, 0, result, &resultSize);
    for(int i = 0; i < resultSize; i++) printf("%d ", result[i]);
    printf("\\n");
    freeGraph(g5);
    
    return 0;
}
