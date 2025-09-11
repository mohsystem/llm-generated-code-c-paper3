#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 9
#define INF INT_MAX

void dijkstra(int graph[V][V], int start) {
    int dist[V];
    bool visited[V];
    int u, v, count, min_dist;

    for (v = 0; v < V; v++) {
        dist[v] = INF;
        visited[v] = false;
    }
    dist[start] = 0;

    for (count = 0; count < V - 1; count++) {
        min_dist = INF;
        for (v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= min_dist)
                min_dist = dist[v], u = v;
        }
        visited[u] = true;

        for (v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] > 0 && dist[v] > dist[u] + graph[u][v])
                dist[v] = dist[u] + graph[u][v];
        }
    }

    // Print shortest distances
    printf("Vertex Distance from Source\n");
    for (v = 0; v < V; v++)
        printf("%d\t\t%d\n", v, dist[v]);
}

int main() {
    // Test cases
    int graphs[][V][V] = {
        {
            {0, 4, 0, 0, 0, 0, 0, 8, 0},
            {4, 0, 8, 0, 0, 0, 0, 11, 0},
            {0, 8, 0, 7, 0, 4, 0, 0, 2},
            {0, 0, 7, 0, 9, 14, 0, 0, 0},
            {0, 0, 0, 9, 0, 10, 0, 0, 0},
            {0, 0, 4, 14, 10, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 2, 0, 1, 6},
            {8, 11, 0, 0, 0, 0, 1, 0, 7},
            {0, 0, 2, 0, 0, 0, 6, 7, 0}
        },
        {
            {0, 1, 0, 0, 0},
            {1, 0, 2, 0, 0},
            {0, 2, 0, 3, 0},
            {0, 0, 3, 0, 1},
            {0, 0, 0, 1, 0}
        },
        {
            {0, 5, 0, 10},
            {5, 0, 3, 0},
            {0, 3, 0, 1},
            {10, 0, 1, 0}
        },
        {
            {0, 2, 0, 6, 0},
            {2, 0, 3, 8, 5},
            {0, 3, 0, 0, 7},
            {6, 8, 0, 0, 9},
            {0, 5, 7, 9, 0}
        },
        {
            {0, 4, 0, 0},
            {4, 0, 8, 0},
            {0, 8, 0, 7},
            {0, 0, 7, 0}
        }
    };

    for (int i = 0; i < 5; i++) {
        printf("Graph %d:\n", i + 1);
        dijkstra(graphs[i], 0);
        printf("\n");
    }

    return 0;
}