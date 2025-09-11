#include <stdio.h>
#include <stdlib.h>

// This is a simplified version and does not include a proper graph data structure
// A real-world implementation would require a more complex data structure and error handling

#define MAX_NODES 100

int visited[MAX_NODES];
int graph[MAX_NODES][MAX_NODES];
int n; // number of nodes

void depthFirstSearch(int start) {
    int i;

    printf("%d ", start);
    visited[start] = 1;

    for (i = 0; i < n; i++) {
        if (graph[start][i] && !visited[i]) {
            depthFirstSearch(i);
        }
    }
}

int main() {
    // Populate graph here

    depthFirstSearch(0);

    return 0;
}