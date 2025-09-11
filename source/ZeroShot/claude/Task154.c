
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

struct Graph {
    int V;
    int adj[MAX_VERTICES][MAX_VERTICES];
};

void initGraph(struct Graph* g, int vertices) {
    g->V = vertices;
    for(int i = 0; i < vertices; i++) {
        for(int j = 0; j < vertices; j++) {
            g->adj[i][j] = 0;
        }
    }
}

void addEdge(struct Graph* g, int v, int w) {
    g->adj[v][w] = 1;
}

void DFSUtil(struct Graph* g, int v, bool* visited, int* result, int* resultSize) {
    visited[v] = true;
    result[(*resultSize)++] = v;
    
    for(int i = 0; i < g->V; i++) {
        if(g->adj[v][i] && !visited[i]) {
            DFSUtil(g, i, visited, result, resultSize);
        }
    }
}

void DFS(struct Graph* g, int start, int* result, int* resultSize) {
    bool* visited = (bool*)calloc(g->V, sizeof(bool));
    *resultSize = 0;
    DFSUtil(g, start, visited, result, resultSize);
    free(visited);
}

int main() {
    // Test Case 1
    struct Graph g1;
    initGraph(&g1, 4);
    addEdge(&g1, 0, 1);
    addEdge(&g1, 0, 2);
    addEdge(&g1, 1, 2);
    addEdge(&g1, 2, 0);
    addEdge(&g1, 2, 3);
    addEdge(&g1, 3, 3);
    int result1[MAX_VERTICES], size1;
    DFS(&g1, 2, result1, &size1);
    printf("DFS from vertex 2: ");
    for(int i = 0; i < size1; i++) printf("%d ", result1[i]);
    printf("\\n");
    
    // Test Case 2
    struct Graph g2;
    initGraph(&g2, 3);
    addEdge(&g2, 0, 1);
    addEdge(&g2, 1, 2);
    int result2[MAX_VERTICES], size2;
    DFS(&g2, 0, result2, &size2);
    printf("DFS from vertex 0: ");
    for(int i = 0; i < size2; i++) printf("%d ", result2[i]);
    printf("\\n");
    
    // Test Case 3
    struct Graph g3;
    initGraph(&g3, 5);
    addEdge(&g3, 0, 1);
    addEdge(&g3, 1, 2);
    addEdge(&g3, 2, 3);
    addEdge(&g3, 3, 4);
    addEdge(&g3, 4, 0);
    int result3[MAX_VERTICES], size3;
    DFS(&g3, 0, result3, &size3);
    printf("DFS from vertex 0: ");
    for(int i = 0; i < size3; i++) printf("%d ", result3[i]);
    printf("\\n");
    
    // Test Case 4
    struct Graph g4;
    initGraph(&g4, 4);
    addEdge(&g4, 0, 1);
    addEdge(&g4, 1, 2);
    addEdge(&g4, 2, 3);
    addEdge(&g4, 3, 0);
    int result4[MAX_VERTICES], size4;
    DFS(&g4, 3, result4, &size4);
    printf("DFS from vertex 3: ");
    for(int i = 0; i < size4; i++) printf("%d ", result4[i]);
    printf("\\n");
    
    // Test Case 5
    struct Graph g5;
    initGraph(&g5, 6);
    addEdge(&g5, 0, 1);
    addEdge(&g5, 0, 2);
    addEdge(&g5, 1, 3);
    addEdge(&g5, 2, 4);
    addEdge(&g5, 3, 5);
    int result5[MAX_VERTICES], size5;
    DFS(&g5, 0, result5, &size5);
    printf("DFS from vertex 0: ");
    for(int i = 0; i < size5; i++) printf("%d ", result5[i]);
    printf("\\n");
    
    return 0;
}
