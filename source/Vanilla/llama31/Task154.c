#include <stdio.h>
#include <stdbool.h>

void dfs(int** graph, int start, bool* visited, int size) {
    visited[start] = true;
    printf("%d ", start);
    for (int i = 0; i < size; i++) {
        if (graph[start][i] == 1 && !visited[i]) {
            dfs(graph, i, visited, size);
        }
    }
}

int main() {
    int size = 5;
    int** graph = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        graph[i] = (int*)malloc(size * sizeof(int));
    }

    // Initialize the graph
    graph[0][0] = 0; graph[0][1] = 1; graph[0][2] = 1; graph[0][3] = 0; graph[0][4] = 0;
    graph[1][0] = 1; graph[1][1] = 0; graph[1][2] = 0; graph[1][3] = 1; graph[1][4] = 0;
    graph[2][0] = 1; graph[2][1] = 0; graph[2][2] = 0; graph[2][3] = 1; graph[2][4] = 1;
    graph[3][0] = 0; graph[3][1] = 1; graph[3][2] = 1; graph[3][3] = 0; graph[3][4] = 0;
    graph[4][0] = 0; graph[4][1] = 0; graph[4][2] = 1; graph[4][3] = 0; graph[4][4] = 0;

    // Test cases
    int startNodes[] = {0, 1, 2, 3, 4};
    for (int i = 0; i < 5; i++) {
        bool* visited = (bool*)calloc(size, sizeof(bool));
        printf("DFS starting from node %d: ", startNodes[i]);
        dfs(graph, startNodes[i], visited, size);
        printf("\n");
        free(visited);
    }

    // Free memory
    for (int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}