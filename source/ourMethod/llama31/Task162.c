#include <stdio.h>
#include <limits.h>

void dijkstra(int** graph, int numNodes, int startNode) {
    int* distances = (int*)malloc(numNodes * sizeof(int));
    int* visited = (int*)malloc(numNodes * sizeof(int));

    // Initialize distances
    for (int i = 0; i < numNodes; i++) {
        distances[i] = INT_MAX;
    }
    distances[startNode] = 0;

    for (int i = 0; i < numNodes; i++) {
        int minDistance = INT_MAX;
        int minIndex = -1;

        // Find the node with the minimum distance that has not been visited
        for (int j = 0; j < numNodes; j++) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                minIndex = j;
            }
        }

        visited[minIndex] = 1;

        // Update distances of adjacent nodes
        for (int j = 0; j < numNodes; j++) {
            if (!visited[j] && graph[minIndex][j] > 0 && distances[minIndex] + graph[minIndex][j] < distances[j]) {
                distances[j] = distances[minIndex] + graph[minIndex][j];
            }
        }
    }

    // Print the shortest distances
    printf("Shortest distances from node %d:\n", startNode);
    for (int i = 0; i < numNodes; i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");

    free(distances);
    free(visited);
}

int main() {
    // Test cases
    int numNodes1 = 9;
    int** graph1 = (int**)malloc(numNodes1 * sizeof(int*));
    for (int i = 0; i < numNodes1; i++) {
        graph1[i] = (int*)malloc(numNodes1 * sizeof(int));
    }
    graph1[0][0] = 0; graph1[0][1] = 4; graph1[0][2] = 0; graph1[0][3] = 0; graph1[0][4] = 0; graph1[0][5] = 0; graph1[0][6] = 0; graph1[0][7] = 8; graph1[0][8] = 0;
    graph1[1][0] = 4; graph1[1][1] = 0; graph1[1][2] = 8; graph1[1][3] = 0; graph1[1][4] = 0; graph1[1][5] = 0; graph1[1][6] = 0; graph1[1][7] = 11; graph1[1][8] = 0;
    graph1[2][0] = 0; graph1[2][1] = 8; graph1[2][2] = 0; graph1[2][3] = 7; graph1[2][4] = 0; graph1[2][5] = 4; graph1[2][6] = 0; graph1[2][7] = 0; graph1[2][8] = 2;
    graph1[3][0] = 0; graph1[3][1] = 0; graph1[3][2] = 7; graph1[3][3] = 0; graph1[3][4] = 9; graph1[3][5] = 14; graph1[3][6] = 0; graph1[3][7] = 0; graph1[3][8] = 0;
    graph1[4][0] = 0; graph1[4][1] = 0; graph1[4][2] = 0; graph1[4][3] = 9; graph1[4][4] = 0; graph1[4][5] = 10; graph1[4][6] = 0; graph1[4][7] = 0; graph1[4][8] = 0;
    graph1[5][0] = 0; graph1[5][1] = 0; graph1[5][2] = 4; graph1[5][3] = 14; graph1[5][4] = 10; graph1[5][5] = 0; graph1[5][6] = 2; graph1[5][7] =