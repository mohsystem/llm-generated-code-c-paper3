#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bfs(int n, int **adjList, int *sizes, int start) {
    bool *visited = (bool *)calloc(n, sizeof(bool));
    int *queue = (int *)malloc(n * sizeof(int));
    int front = 0, back = 0;
    
    visited[start] = true;
    queue[back++] = start;
    
    while (front < back) {
        int node = queue[front++];
        printf("%d ", node);
        
        for (int i = 0; i < sizes[node]; i++) {
            int neighbor = adjList[node][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue[back++] = neighbor;
            }
        }
    }
    
    printf("\n");
    free(visited);
    free(queue);
}

int main() {
    int n = 5;
    
    int sizes[] = {2, 3, 2, 1, 2};
    int *adjList[5];
    
    int a0[] = {1, 2};
    int a1[] = {0, 3, 4};
    int a2[] = {0, 4};
    int a3[] = {1};
    int a4[] = {1, 2};
    
    adjList[0] = a0;
    adjList[1] = a1;
    adjList[2] = a2;
    adjList[3] = a3;
    adjList[4] = a4;
    
    bfs(n, adjList, sizes, 0); // Output: 0 1 2 3 4
    bfs(n, adjList, sizes, 1); // Output: 1 0 3 4 2
    bfs(n, adjList, sizes, 2); // Output: 2 0 4 1 3
    bfs(n, adjList, sizes, 3); // Output: 3 1 0 4 2
    bfs(n, adjList, sizes, 4); // Output: 4 1 2 0 3
    
    return 0;
}