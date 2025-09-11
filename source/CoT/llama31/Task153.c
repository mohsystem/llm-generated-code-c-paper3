#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100

void bfs(int graph[][MAX], int vertices, int start) {
    bool visited[vertices];
    int queue[vertices];
    int front = 0, rear = 0;

    for (int i = 0; i < vertices; i++) {
        visited[i] = false;
    }

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);

        for (int i = 0; i < vertices; i++) {
            if (graph[vertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
}

int main() {
    // Test cases
    int graph1[][MAX] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0}
    };
    printf("BFS Traversal starting from node 0:\n");
    bfs(graph1, 5, 0);
    printf("\n");

    int graph2[][MAX] = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 1, 0, 1, 0}
    };
    printf("BFS Traversal starting from node 1:\n");
    bfs(graph2, 5, 1);
    printf("\n");

    int graph3[][MAX] = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {0, 1, 1, 0}
    };
    printf("BFS Traversal starting from node 2:\n");
    bfs(graph3, 4, 2);
    printf("\n");

    int graph4[][MAX] = {
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 1},
        {0, 1, 1, 0}
    };
    printf("BFS Traversal starting from node 3:\n");
    bfs(graph4, 4, 3);
    printf("\n");

    int graph5[][MAX] = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };
    printf("BFS Traversal starting from node 0:\n");
    bfs(graph5, 4, 0);
    printf("\n");

    return 0;
}