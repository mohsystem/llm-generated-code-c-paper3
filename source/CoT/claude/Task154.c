
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct Graph {
    int V;
    int adj[MAX_VERTICES][MAX_VERTICES];
} Graph;

void initGraph(Graph* g, int v) {
    if(v > 0 && v <= MAX_VERTICES) {
        g->V = v;
        for(int i = 0; i < v; i++) {
            for(int j = 0; j < v; j++) {
                g->adj[i][j] = 0;
            }
        }
    }
}

void addEdge(Graph* g, int v, int w) {
    if(v >= 0 && v < g->V && w >= 0 && w < g->V) {
        g->adj[v][w] = 1;
    }
}

void dfsUtil(Graph* g, int v, bool* visited, int* result, int* size) {
    visited[v] = true;
    result[(*size)++] = v;
    
    for(int i = 0; i < g->V; i++) {
        if(g->adj[v][i] && !visited[i]) {
            dfsUtil(g, i, visited, result, size);
        }
    }
}

void dfs(Graph* g, int start, int* result, int* size) {
    if(start < 0 || start >= g->V) {
        *size = 0;
        return;
    }
    
    bool* visited = (bool*)calloc(g->V, sizeof(bool));
    if(visited == NULL) {
        *size = 0;
        return;
    }
    
    *size = 0;
    dfsUtil(g, start, visited, result, size);
    
    free(visited);
}

int main() {
    int result[MAX_VERTICES];
    int size;
    
    // Test Case 1: Simple path graph
    Graph g1;
    initGraph(&g1, 4);
    addEdge(&g1, 0, 1);
    addEdge(&g1, 1, 2);
    addEdge(&g1, 2, 3);
    printf("Test 1: ");
    dfs(&g1, 0, result, &size);
    for(int i = 0; i < size; i++) printf("%d ", result[i]);
    printf("\\n");
    
    // Test Case 2: Cyclic graph
    Graph g2;
    initGraph(&g2, 4);
    addEdge(&g2, 0, 1);
    addEdge(&g2, 1, 2);
    addEdge(&g2, 2, 3);
    addEdge(&g2, 3, 0);
    printf("Test 2: ");
    dfs(&g2, 0, result, &size);
    for(int i = 0; i < size; i++) printf("%d ", result[i]);
    printf("\\n");
    
    // Test Case 3: Disconnected graph
    Graph g3;
    initGraph(&g3, 4);
    addEdge(&g3, 0, 1);
    addEdge(&g3, 2, 3);
    printf("Test 3: ");
    dfs(&g3, 0, result, &size);
    for(int i = 0; i < size; i++) printf("%d ", result[i]);
    printf("\\n");
    
    // Test Case 4: Single node
    Graph g4;
    initGraph(&g4, 1);
    printf("Test 4: ");
    dfs(&g4, 0, result, &size);
    for(int i = 0; i < size; i++) printf("%d ", result[i]);
    printf("\\n");
    
    // Test Case 5: Invalid start node
    Graph g5;
    initGraph(&g5, 4);
    addEdge(&g5, 0, 1);
    addEdge(&g5, 1, 2);
    printf("Test 5: ");
    dfs(&g5, 5, result, &size);
    for(int i = 0; i < size; i++) printf("%d ", result[i]);
    printf("\\n");
    
    return 0;
}
