#include <stdio.h>
#include <stdlib.h>

// This C code does not support creating dynamic graphs as it is not a dynamically typed language.
// Instead, the graph is hardcoded for simplicity.

#define MAX_NODES 100
#define TRUE 1
#define FALSE 0

int adjMatrix[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
int queue[MAX_NODES];
int front = -1, rear = -1;

void enqueue(int node) {
    if (rear == MAX_NODES - 1)
        printf("Queue is full.\n");
    else {
        if (front == -1)
            front = 0;
        rear++;
        queue[rear] = node;
    }
}

int dequeue() {
    int node;
    if (front == -1 || front > rear) {
        printf("Queue is empty.\n");
        return -1;
    } else {
        node = queue[front];
        front++;
        return node;
    }
}

void bfs(int startNode, int numNodes) {
    int i, node;

    visited[startNode] = TRUE;
    enqueue(startNode);

    while (front <= rear) {
        node = dequeue();
        printf("%d ", node);

        for (i = 0; i < numNodes; i++) {
            if (adjMatrix[node][i] && !visited[i]) {
                visited[i] = TRUE;
                enqueue(i);
            }
        }
    }
}

int main() {
    int i, j;
    int numNodes = 4;
    int startNode = 2;

    // Hardcoded graph
    int edges[4][2] = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};

    // Initialize adjacency matrix
    for (i = 0; i < numNodes; i++) {
        for (j = 0; j < numNodes; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    // Add edges to the graph
    for (i = 0; i < sizeof(edges) / sizeof(edges[0]); i++) {
        adjMatrix[edges[i][0]][edges[i][1]] = 1;
        adjMatrix[edges[i][1]][edges[i][0]] = 1;
    }

    bfs(startNode, numNodes);

    return 0;
}