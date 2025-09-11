#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct {
    int items[MAX_NODES];
    int front;
    int rear;
} Queue;

void enqueue(Queue* q, int value) {
    q->items[++q->rear] = value;
}

int dequeue(Queue* q) {
    return q->items[q->front++];
}

bool isEmpty(Queue* q) {
    return q->front > q->rear;
}

void bfs(int graph[MAX_NODES][MAX_NODES], int num_nodes, int start) {
    bool visited[MAX_NODES] = {false};
    Queue q = {.front = 0, .rear = -1};

    enqueue(&q, start);
    visited[start] = true;

    while (!isEmpty(&q)) {
        int node = dequeue(&q);
        printf("%d ", node);

        for (int i = 0; i < num_nodes; ++i) {
            if (graph[node][i] && !visited[i]) {
                enqueue(&q, i);
                visited[i] = true;
            }
        }
    }
    printf("\n");
}

int main() {
    int graph[MAX_NODES][MAX_NODES] = {0};
    graph[1][2] = graph[1][3] = 1;
    graph[2][4] = 1;
    graph[3][4] = graph[3][5] = 1;

    for (int start = 1; start <= 5; ++start) {
        bfs(graph, 6, start); // Test with nodes 1 through 5
    }

    return 0;
}