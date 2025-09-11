#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct {
    int nodes[MAX_NODES];
    int size;
} AdjList;

void dfs(AdjList* graph, int start, bool* visited) {
    visited[start] = true;
    printf("%d ", start);
    for (int i = 0; i < graph[start].size; i++) {
        if (!visited[graph[start].nodes[i]]) {
            dfs(graph, graph[start].nodes[i], visited);
        }
    }
}

int main() {
    int numNodes = 5;
    AdjList* graph = (AdjList*)malloc(numNodes * sizeof(AdjList));
    graph[0].nodes[0] = 1; graph[0].nodes[1] = 2; graph[0].size = 2;
    graph[1].nodes[0] = 2; graph[1].nodes[1] = 0; graph[1].nodes[2] = 3; graph[1].nodes[3] = 4; graph[1].size = 4;
    graph[2].nodes[0] = 0; graph[2].nodes[1] = 1; graph[2].nodes[2] = 4; graph[2].size = 3;
    graph[3].nodes[0] = 1; graph[3].size = 1;
    graph[4].nodes[0] = 1; graph[4].nodes[1] = 2; graph[4].size = 2;

    bool* visited = (bool*)calloc(numNodes, sizeof(bool));
    dfs(graph, 0, visited);

    free(graph);
    free(visited);
    return 0;
}