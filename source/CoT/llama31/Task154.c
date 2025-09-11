#include <stdio.h>
#include <stdbool.h>

void dfs(int** graph, int* edges, int start, bool* visited, int numVertices) {
    visited[start] = true;
    printf("%d ", start);
    for (int i = 0; i < edges[start]; i++) {
        int neighbor = graph[start][i];
        if (!visited[neighbor]) {
            dfs(graph, edges, neighbor, visited, numVertices);
        }
    }
}

int main() {
    // Test case 1
    int numVertices1 = 5;
    int edges1[] = {2, 1, 1, 0, 0};
    int** graph1 = (int**)malloc(numVertices1 * sizeof(int*));
    for (int i = 0; i < numVertices1; i++) {
        graph1[i] = (int*)malloc(edges1[i] * sizeof(int));
    }
    graph1[0][0] = 1; graph1[0][1] = 2;
    graph1[1][0] = 3;
    graph1[2][0] = 4;
    bool visited1[5] = {false};
    printf("DFS Traversal starting from node 0: ");
    dfs(graph1, edges1, 0, visited1, numVertices1);
    printf("\n");

    // Test case 2
    int numVertices2 = 6;
    int edges2[] = {2, 1, 1, 1, 0, 0};
    int** graph2 = (int**)malloc(numVertices2 * sizeof(int*));
    for (int i = 0; i < numVertices2; i++) {
        graph2[i] = (int*)malloc(edges2[i] * sizeof(int));
    }
    graph2[0][0] = 1; graph2[0][1] = 2;
    graph2[1][0] = 3;
    graph2[2][0] = 4;
    graph2[3][0] = 5;
    bool visited2[6] = {false};
    printf("DFS Traversal starting from node 0: ");
    dfs(graph2, edges2, 0, visited2, numVertices2);
    printf("\n");

    // Test case 3
    int numVertices3 = 4;
    int edges3[] = {1, 1, 1, 0};
    int** graph3 = (int**)malloc(numVertices3 * sizeof(int*));
    for (int i = 0; i < numVertices3; i++) {
        graph3[i] = (int*)malloc(edges3[i] * sizeof(int));
    }
    graph3[0][0] = 1;
    graph3[1][0] = 2;
    graph3[2][0] = 3;
    bool visited3[4] = {false};
    printf("DFS Traversal starting from node 0: ");
    dfs(graph3, edges3, 0, visited3, numVertices3);
    printf("\n");

    // Test case 4
    int numVertices4 = 3;
    int edges4[] = {1, 1, 0};
    int** graph4 = (int**)malloc(numVertices4 * sizeof(int*));
    for (int i = 0; i < numVertices4; i++) {
        graph4[i] = (int*)malloc(edges4[i] * sizeof(int));
    }
    graph4[0][0] = 1;
    graph4[1][0] = 2;
    bool visited4[3] = {false};
    printf("DFS Traversal starting from node 0: ");
    dfs(graph4, edges4, 0, visited4, numVertices4);
    printf("\n");

    // Test case 5
    int numVertices5 = 2;
    int edges5[] = {1, 0};
    int** graph5 = (int**)malloc(numVertices5 * sizeof(int*));
    for (int i = 0; i < numVertices5; i++) {
        graph5[i] = (int*)malloc(edges5[i] * sizeof(int));
    }
    graph5[0][0] = 1;
    bool visited5[2] = {false};
    printf("DFS Traversal starting from node 0: ");
    dfs(graph5, edges5, 0, visited5, numVertices5);
    printf("\n");

    return 0;
}