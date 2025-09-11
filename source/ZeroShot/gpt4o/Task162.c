#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct {
    int id;
    int cost;
} Node;

typedef struct {
    Node *data;
    int size;
} PriorityQueue;

void pq_init(PriorityQueue *pq) {
    pq->data = malloc(sizeof(Node) * MAX_NODES);
    pq->size = 0;
}

void pq_push(PriorityQueue *pq, int id, int cost) {
    pq->data[pq->size].id = id;
    pq->data[pq->size].cost = cost;
    pq->size++;
}

Node pq_pop(PriorityQueue *pq) {
    int minIndex = 0;
    for (int i = 1; i < pq->size; i++) {
        if (pq->data[i].cost < pq->data[minIndex].cost) {
            minIndex = i;
        }
    }
    Node minNode = pq->data[minIndex];
    pq->data[minIndex] = pq->data[pq->size - 1];
    pq->size--;
    return minNode;
}

bool pq_empty(PriorityQueue *pq) {
    return pq->size == 0;
}

void dijkstra(int graph[MAX_NODES][MAX_NODES], int nodes, int start) {
    int distances[MAX_NODES];
    bool visited[MAX_NODES] = {false};
    PriorityQueue pq;

    for (int i = 0; i < nodes; i++) {
        distances[i] = INT_MAX;
    }
    distances[start] = 0;

    pq_init(&pq);
    pq_push(&pq, start, 0);

    while (!pq_empty(&pq)) {
        Node current = pq_pop(&pq);

        if (visited[current.id]) {
            continue;
        }

        visited[current.id] = true;

        for (int i = 0; i < nodes; i++) {
            if (graph[current.id][i] != 0 && !visited[i]) {
                int newDist = distances[current.id] + graph[current.id][i];
                if (newDist < distances[i]) {
                    distances[i] = newDist;
                    pq_push(&pq, i, newDist);
                }
            }
        }
    }

    for (int i = 0; i < nodes; i++) {
        printf("Node: %d Distance: %d\n", i, distances[i]);
    }

    free(pq.data);
}

int main() {
    int graph[MAX_NODES][MAX_NODES] = {0};
    graph[0][1] = 4;
    graph[0][2] = 1;
    graph[1][3] = 1;
    graph[2][1] = 2;
    graph[2][3] = 5;

    dijkstra(graph, 4, 0);

    return 0;
}