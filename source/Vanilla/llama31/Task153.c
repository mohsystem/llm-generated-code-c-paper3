#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NODES 100

void bfs(int** graph, int numNodes, int start) {
    bool* visited = (bool*)calloc(numNodes, sizeof(bool));
    int* queue = (int*)calloc(numNodes, sizeof(int));
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = true;

    while (front < rear) {
        int node = queue[front++];
        printf("%d ", node);

        for (int i = 0; i < numNodes; i++) {
            if (graph[node][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = true;
            }
        }
    }

    free(queue);
    free(visited);
}

int main() {
    // Test cases
    int numNodes1 = 5;
    int** graph1 = (int**)calloc(numNodes1, sizeof(int*));
    for (int i = 0; i < numNodes1; i++) {
        graph1[i] = (int*)calloc(numNodes1, sizeof(int));
    }
    graph1[0][1] = graph1[0][2] = graph1[0][3] = 1;
    graph1[1][0] = graph1[1][3] = 1;
    graph1[2][0] = graph1[2][3] = 1;
    graph1[3][0] = graph1[3][1] = graph1[3][2] = 1;

    printf("BFS Traversal starting from node 0: ");
    bfs(graph1, numNodes1, 0);
    printf("\n");

    for (int i = 0; i < numNodes1; i++) {
        free(graph1[i]);
    }
    free(graph1);

    int numNodes2 = 5;
    int** graph2 = (int**)calloc(numNodes2, sizeof(int*));
    for (int i = 0; i < numNodes2; i++) {
        graph2[i] = (int*)calloc(numNodes2, sizeof(int));
    }
    graph2[0][1] = graph2[0][4] = 1;
    graph2[1][0] = graph2[1][2] = 1;
    graph2[2][1] = graph2[2][3] = 1;
    graph2[3][2] = graph2[3][4] = 1;
    graph2[4][0] = graph2[4][3] = 1;

    printf("BFS Traversal starting from node 1: ");
    bfs(graph2, numNodes2, 1);
    printf("\n");

    for (int i = 0; i < numNodes2; i++) {
        free(graph2[i]);
    }
    free(graph2);

    int numNodes3 = 4;
    int** graph3 = (int**)calloc(numNodes3, sizeof(int*));
    for (int i = 0; i < numNodes3; i++) {
        graph3[i] = (int*)calloc(numNodes3, sizeof(int));
    }
    graph3[0][2] = 1;
    graph3[1][3] = 1;
    graph3[2][0] = graph3[2][3] = 1;
    graph3[3][1] = graph3[3][2] = 1;

    printf("BFS Traversal starting from node 2: ");
    bfs(graph3, numNodes3, 2);
    printf("\n");

    for (int i = 0; i < numNodes3; i++) {
        free(graph3[i]);
    }
    free(graph3);

    int numNodes4 = 4;
    int** graph4 = (int**)calloc(numNodes4, sizeof(int*));
    for (int i = 0; i < numNodes4; i++) {
        graph4[i] = (int*)calloc(numNodes4, sizeof(int));
    }
    graph4[0][1] = 1;
    graph4[1][0] = graph4[1][2] = graph4[1][3] = 1;
    graph4[2][1] = graph4[2][3] = 1;
    graph4[3][1] = graph4[3][2] = 1;

    printf("BFS Traversal starting from node 0: ");
    bfs(graph4, numNodes4, 0);
    printf("\n");

    for (int i = 0; i < numNodes4; i++) {
        free(graph4[i]);
    }
    free(graph4);

    int numNodes5 = 4;
    int** graph5 = (int**)calloc(numNodes5, sizeof(int*));
    for (int i = 0; i < numNodes5; i++) {
        graph5[i] = (int*)calloc(numNodes5, sizeof(int));
    }

    printf("BFS Traversal starting from node 0: ");
    bfs(graph5, numNodes5, 0);
    printf("\n");

    for (int i = 0; i < numNodes5; i++) {
        free(graph5[i]);
    }
    free(graph5);

    return 0;
}