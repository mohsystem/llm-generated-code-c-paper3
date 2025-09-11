#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int *array;
    int size;
    int capacity;
} Vector;

typedef struct {
    Vector *array[MAX];
    int size;
} Graph;

void initVector(Vector *vec, int capacity) {
    vec->array = (int *)malloc(capacity * sizeof(int));
    vec->size = 0;
    vec->capacity = capacity;
}

void pushBack(Vector *vec, int value) {
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        vec->array = (int *)realloc(vec->array, vec->capacity * sizeof(int));
    }
    vec->array[vec->size++] = value;
}

void initGraph(Graph *graph) {
    for (int i = 0; i < MAX; i++) {
        graph->array[i] = NULL;
    }
    graph->size = 0;
}

void addEdge(Graph *graph, int src, int dest) {
    if (graph->array[src] == NULL) {
        graph->array[src] = (Vector *)malloc(sizeof(Vector));
        initVector(graph->array[src], 1);
    }
    pushBack(graph->array[src], dest);
}

void depthFirstSearch(Graph *graph, int startNode, int *visited, int *result, int *resultSize) {
    int stack[MAX];
    int top = -1;
    stack[++top] = startNode;
    
    while (top >= 0) {
        int node = stack[top--];
        if (!visited[node]) {
            visited[node] = 1;
            result[(*resultSize)++] = node;
            if (graph->array[node]) {
                for (int i = graph->array[node]->size - 1; i >= 0; i--) {
                    int neighbor = graph->array[node]->array[i];
                    if (!visited[neighbor]) {
                        stack[++top] = neighbor;
                    }
                }
            }
        }
    }
}

int main() {
    Graph graph1;
    initGraph(&graph1);
    addEdge(&graph1, 0, 1);
    addEdge(&graph1, 0, 2);
    addEdge(&graph1, 1, 0);
    addEdge(&graph1, 1, 3);
    addEdge(&graph1, 1, 4);
    addEdge(&graph1, 2, 0);
    addEdge(&graph1, 3, 1);
    addEdge(&graph1, 4, 1);
    addEdge(&graph1, 4, 5);
    addEdge(&graph1, 5, 4);

    int visited[MAX] = {0};
    int result[MAX];
    int resultSize = 0;

    depthFirstSearch(&graph1, 0, visited, result, &resultSize);
    for (int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n"); // Example output: 0 1 3 4 5 2

    return 0;
}