#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NODES 100

// Structure for a node in the priority queue
typedef struct {
    int node;
    int distance;
} Node;

// Function to swap two nodes
void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the priority queue
void heapify(Node heap[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].distance < heap[smallest].distance) {
        smallest = left;
    }

    if (right < n && heap[right].distance < heap[smallest].distance) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, n, smallest);
    }
}

// Function to extract the minimum node from the priority queue
Node extractMin(Node heap[], int* n) {
    Node min = heap[0];
    heap[0] = heap[*n - 1];
    (*n)--;
    heapify(heap, *n, 0);
    return min;
}

// Function to insert a node into the priority queue
void insert(Node heap[], int* n, Node node) {
    heap[*n] = node;
    (*n)++;
    int i = *n - 1;

    while (i > 0 && heap[(i - 1) / 2].distance > heap[i].distance) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void dijkstra(int graph[][MAX_NODES], int start, int n) {
    int distances[n];
    bool visited[n];

    for (int i = 0; i < n; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }

    distances[start] = 0;

    Node heap[n];
    int heapSize = 0;
    insert(heap, &heapSize, (Node){start, 0});

    while (heapSize > 0) {
        Node node = extractMin(heap, &heapSize);
        int currentNode = node.node;
        int currentDistance = node.distance;

        if (currentDistance > distances[currentNode]) {
            continue;
        }

        visited[currentNode] = true;

        for (int neighbor = 0; neighbor < n; neighbor++) {
            if (graph[currentNode][neighbor] > 0 && !visited[neighbor]) {
                int newDistance = currentDistance + graph[currentNode][neighbor];
                if (newDistance < distances[neighbor]) {
                    distances[neighbor] = newDistance;
                    insert(heap, &heapSize, (Node){neighbor, newDistance});
                }
            }
        }
    }

    // Print distances
    for (int i = 0; i < n; i++) {
        printf("Shortest distance from %d to %d: %d\n", start, i, distances[i]);
    }
}

int main() {
    // Test cases
    int graph1[][9] = {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 4, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 4, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };
    dijkstra(graph1, 0, 9);

    int graph2[][4] = {
        {0, 2, 0, 6},
        {2, 0, 3, 8},
        {0, 3, 0, 0},
        {6, 8, 0, 0}
    };
    dijkstra(graph2, 0, 4);

    int graph3[][4] = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };
    dijkstra(graph3, 0, 4);

    int graph4[][4] = {
        {0, 3, 0, 0},
        {3, 0, 2, 0},
        {0, 2, 0, 1},
        {0, 0, 1, 0}
    };
    dijkstra(graph4, 0, 4);

    int graph5[][4] = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}
    };
    dijkstra(graph5, 0, 4);

    return 0;
}