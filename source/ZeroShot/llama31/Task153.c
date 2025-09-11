#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void bfs(int** graph, int numNodes, int start) {
    bool* visited = (bool*)calloc(numNodes, sizeof(bool));
    int* queue = (int*)malloc(numNodes * sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = true;

    while (front < rear) {
        int node = queue[front++];
        printf("%d ", node);

        for (int neighbor = 0; neighbor < numNodes; neighbor++) {
            if (graph[node][neighbor] == 1 && !visited[neighbor]) {
                queue[rear++] = neighbor;
                visited[neighbor] = true;
            }
        }
    }

    free(visited);
    free(queue);
}

int main() {
    // Test cases
    int numNodes = 5;
    int** graphs[] = {
        (int**)malloc(numNodes * sizeof(int*)),
        (int**)malloc(numNodes * sizeof(int*)),
        (int**)malloc(numNodes * sizeof(int*)),
        (int**)malloc(numNodes * sizeof(int*)),
        (int**)malloc(numNodes * sizeof(int*))
    };

    // Initialize graphs
    for (int i = 0; i < numNodes; i++) {
        graphs[0][i] = (int*)malloc(numNodes * sizeof(int));
        graphs[1][i] = (int*)malloc(numNodes * sizeof(int));
        graphs[2][i] = (int*)malloc(numNodes * sizeof(int));
        graphs[3][i] = (int*)malloc(numNodes * sizeof(int));
        graphs[4][i] = (int*)malloc(numNodes * sizeof(int));
    }

    // Assign values to graphs
    int graph1[][5] = {
        {0, 1, 1, 0, 0},
        {1, 0, 0, 1, 0},
        {1, 0, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    int graph2[][5] = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1},
        {0, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {1, 1, 0, 1, 0}
    };
    int graph3[][5] = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 1, 0, 1},
        {0, 0, 1, 1, 0}
    };
    int graph4[][5] = {
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {0, 1, 0, 1, 0}
    };
    int graph5[][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            graphs[0][i][j] = graph1[i][j];
            graphs[1][i][j] = graph2[i][j];
            graphs[2][i][j] = graph3[i][j];
            graphs[3][i][j] = graph4[i][j];
            graphs[4][i][j] = graph5[i][j];
        }
    }

    for (int i = 0; i < 5; i++) {
        printf("BFS Traversal starting from node %d:\n", i);
        bfs(graphs[i], numNodes, i);
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < numNodes; i++) {
        free(graphs[0][i]);
        free(graphs[1][i]);
        free(graphs[2][i]);
        free(graphs[3][i]);
        free(graphs[4][i]);
    }
    free(graphs[0]);
    free(graphs[1]);
    free(graphs[2]);
    free(graphs[3]);
    free(graphs[4]);

    return 0;
}