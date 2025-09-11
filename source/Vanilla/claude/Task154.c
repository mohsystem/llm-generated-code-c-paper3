
#include <stdio.h>
#include <stdlib.h>

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

void DFSUtil(struct Graph* graph, int v, int* visited, int* result, int* size) {
    visited[v] = 1;
    result[(*size)++] = v;
    
    for(int i = 0; i < graph->V; i++) {
        if(graph->adj[v][i] && !visited[i]) {
            DFSUtil(graph, i, visited, result, size);
        }
    }
}

int* DFS(struct Graph* graph, int start, int* resultSize) {
    int* visited = (int*)calloc(graph->V, sizeof(int));
    int* result = (int*)malloc(graph->V * sizeof(int));
    *resultSize = 0;
    
    DFSUtil(graph, start, visited, result, resultSize);
    
    free(visited);
    return result;
}

void freeGraph(struct Graph* graph) {
    for(int i = 0; i < graph->V; i++) {
        free(graph->adj[i]);
    }
    free(graph->adj);
    free(graph);
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
    int size1;
    int* result1 = DFS(g1, 2, &size1);
    printf("DFS starting from vertex 2: ");
    for(int i = 0; i < size1; i++) printf("%d ", result1[i]);
    printf("\\n");
    
    // Test Case 2
    struct Graph* g2 = createGraph(3);
    addEdge(g2, 0, 1);
    addEdge(g2, 1, 2);
    int size2;
    int* result2 = DFS(g2, 0, &size2);
    printf("DFS starting from vertex 0: ");
    for(int i = 0; i < size2; i++) printf("%d ", result2[i]);
    printf("\\n");
    
    // Test Case 3
    struct Graph* g3 = createGraph(5);
    addEdge(g3, 0, 1);
    addEdge(g3, 0, 2);
    addEdge(g3, 1, 3);
    addEdge(g3, 2, 4);
    int size3;
    int* result3 = DFS(g3, 0, &size3);
    printf("DFS starting from vertex 0: ");
    for(int i = 0; i < size3; i++) printf("%d ", result3[i]);
    printf("\\n");
    
    // Test Case 4
    struct Graph* g4 = createGraph(4);
    addEdge(g4, 0, 1);
    addEdge(g4, 1, 2);
    addEdge(g4, 2, 3);
    addEdge(g4, 3, 0);
    int size4;
    int* result4 = DFS(g4, 0, &size4);
    printf("DFS starting from vertex 0: ");
    for(int i = 0; i < size4; i++) printf("%d ", result4[i]);
    printf("\\n");
    
    // Test Case 5
    struct Graph* g5 = createGraph(1);
    int size5;
    int* result5 = DFS(g5, 0, &size5);
    printf("DFS starting from vertex 0: ");
    for(int i = 0; i < size5; i++) printf("%d ", result5[i]);
    printf("\\n");
    
    // Free memory
    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    freeGraph(g1);
    freeGraph(g2);
    freeGraph(g3);
    freeGraph(g4);
    freeGraph(g5);
    
    return 0;
}
