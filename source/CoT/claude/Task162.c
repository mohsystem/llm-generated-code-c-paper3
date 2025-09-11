
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5
#define INF INT_MAX

int minDistance(int dist[], bool visited[]) {
    int min = INF;
    int minIndex = -1;

    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf("%d ", j);
}

void printSolution(int dist[], int parent[], int src) {
    printf("Vertex \\t\\t Distance \\tPath\\n");
    for (int i = 0; i < V; i++) {
        if (i != src) {
            printf("%d \\t\\t %d \\t\\t", i, dist[i]);
            printPath(parent, i);
            printf("\\n");
        }
    }
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];
    bool visited[V];
    int parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        if (u == -1) break;
        visited[u] = true;
        //todo error: missing terminating ' character
        //incomplete code
        // 61 | dist[u] + graph[u', type='text
        // ')
        //
        // for (int v = 0; v < V; v++) {
        //     if (!visited[v] && graph[u][v] &&
        //         dist[u] != INF &&
        //     dist[u] + graph[u', type='text')
    }
}