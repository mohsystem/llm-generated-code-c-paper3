#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define V 5
#define INFINITY INT_MAX

int minDistance(int dist[], bool sptSet[]) {
    int min = INFINITY, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[], int start) {
    printf("Shortest path from node %d:\n", start);
    for (int i = 0; i < V; i++)
        printf("To node %d: %d\n", i, dist[i]);
}

void dijkstra(int graph[V][V], int start) {
    int dist[V];
    bool sptSet[V];

    for (int i = 0; i < V; i++)
        dist[i] = INFINITY, sptSet[i] = false;

    dist[start] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INFINITY && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist, start);
}

int main() {
    int graph[V][V] = {
        {0, 10, 20, 0, 0},
        {10, 0, 5, 2, 0},
        {20, 5, 0, 15, 6},
        {0, 2, 15, 0, 1},
        {0, 0, 6, 1, 0}
    };

    dijkstra(graph, 0);

    return 0;
}