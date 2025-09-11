
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct Graph {
    int vertices;
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

void initGraph(Graph* g, int vertices) {
    if(vertices > 0 && vertices <= MAX_VERTICES) {
        g->vertices = vertices;
        for(int i = 0; i < vertices; i++) {
            for(int j = 0; j < vertices; j++) {
                g->adjacencyMatrix[i][j] = 0;
            }
        }
    }
}

void addEdge(Graph* g, int v, int w) {
    if(v >= 0 && v < g->vertices && w >= 0 && w < g->vertices) {
        g->adjacencyMatrix[v][w] = 1;
    }
}

void dfsUtil(Graph* g, int vertex, bool* visited, int* result, int* resultSize) {
    visited[vertex] = true;
    result[(*resultSize)++] = vertex;
    
    for(int i = 0; i < g->vertices; i++) {
        if(g->adjacencyMatrix[vertex][i] && !visited[i]) {
            dfsUtil(g, i, visited, result, resultSize);
        }
    }
}

int* dfs(Graph* g, int startVertex, int* resultSize) {
    if(startVertex < 0 || startVertex >= g->vertices) {
        *resultSize = 0;
        return NULL;
    }
    
    bool* visited = (bool*)calloc(g->vertices, sizeof(bool));
    int* result = (int*)malloc(g->vertices * sizeof(int));
    *resultSize = 0;
    
    if(visited && result) {
        dfsUtil(g, startVertex, visited, result, resultSize);
    }
    
    free(visited);
    return result;
}

int main() {
    // Test case 1: Simple graph
    Graph g1;
    initGraph(&g1, 4);
    addEdge(&g1, 0, 1);
    addEdge(&g1, 0, 2);
    addEdge(&g1, 1, 2);
    addEdge(&g1, 2, 0);
    addEdge(&g1, 2, 3);
    addEdge(&g1, 3, 3);
    
    int resultSize;
    int* result = dfs(&g1, 2, &resultSize);
    printf("DFS from vertex 2: ");
    for(int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\\n");
    free(result);
    
    // Test case 2: Single node
    Graph g2;
    initGraph(&g2, 1);
    result = dfs(&g2, 0, &resultSize);
    printf("DFS from vertex 0: ");
    for(int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\\n");
    free(result);
    
    // Test case 3: Disconnected graph
    Graph g3;
    initGraph(&g3, 4);
    addEdge(&g3, 0, 1);
    addEdge(&g3, 2, 3);
    result = dfs(&g3, 0, &resultSize);
    printf("DFS from vertex 0: ");
    for(int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\\n");
    free(result);
    
    // Test case 4: Linear graph
    Graph g4;
    initGraph(&g4, 4);
    addEdge(&g4, 0, 1);
    addEdge(&g4, 1, 2);
    addEdge(&g4, 2, 3);
    result = dfs(&g4, 0, &resultSize);
    printf("DFS from vertex 0: ");
    for(int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\\n");
    free(result);
    
    // Test case 5: Invalid input
    Graph g5;
    initGraph(&g5, 4);
    addEdge(&g5, 0, 1);
    result = dfs(&g5, -1, &resultSize);
    printf("DFS from invalid vertex: ");
    if(result == NULL) {
        printf("Invalid input\\n");
    }
    
    return 0;
}
