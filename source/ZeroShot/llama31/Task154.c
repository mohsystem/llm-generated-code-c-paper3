#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void dfs(int** graph, int* edges, int numVertices, int start, bool* visited) {
    visited[start] = true;
    printf("%d ", start);
    for (int i = 0; i < edges[start]; i++) {
        int neighbor = graph[start][i];
        if (!visited[neighbor]) {
            dfs(graph, edges, numVertices, neighbor, visited);
        }
    }
}

int main() {
    int numVertices = 6;
    int* edges = (int*)malloc(numVertices * sizeof(int));
    int** graph = (int**)malloc(numVertices * sizeof(int*));

    edges[0] = 2; edges[1] = 1; edges[2] = 1; edges[3] = 1; edges[4] = 0; edges[5] = 0;

    graph[0] = (int*)malloc(2 * sizeof(int)); graph[0][0] = 1; graph[0][1] = 2;
    graph[1] = (int*)malloc(1 * sizeof(int)); graph[1][0] = 3;
    graph[2] = (int*)malloc(1 * sizeof(int)); graph[2][0] = 4;
    graph[3] = (int*)malloc(1 * sizeof(int)); graph[3][0] = 5;
    graph[4] = NULL; graph[5] = NULL;

    // Test cases
    for (int i = 0; i < 5; i++) {
        bool* visited = (bool*)calloc(numVertices, sizeof(bool));
        printf("DFS starting from node %d: ", i);
        dfs(graph, edges, numVertices, i, visited);
        printf("\n");
        free(visited);
    }

    for (int i = 0; i < numVertices; i++) {
        if (graph[i] != NULL) free(graph[i]);
    }
    free(graph);
    free(edges);

    return 0;
}