#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX 1000

// Structure to represent a node in the priority queue
typedef struct Node {
    int vertex;
    int weight;
} Node;

// Function to swap two nodes
void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the priority queue
void heapify(Node* heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].weight < heap[smallest].weight) {
        smallest = left;
    }

    if (right < size && heap[right].weight < heap[smallest].weight) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, size, smallest);
    }
}

// Function to extract the minimum element from the priority queue
Node extractMin(Node* heap, int* size) {
    Node min = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify(heap, *size, 0);
    return min;
}

// Function to insert a node into the priority queue
void insert(Node* heap, int* size, Node node) {
    heap[*size] = node;
    (*size)++;
    int i = *size - 1;
    while (i > 0 && heap[(i - 1) / 2].weight > heap[i].weight) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Dijkstra's algorithm
void dijkstra(int** graph, int V, int source) {
    int* dist = (int*)calloc(V, sizeof(int));
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
    }
    dist[source] = 0;

    bool* visited = (bool*)calloc(V, sizeof(bool));

    Node* heap = (Node*)malloc(V * sizeof(Node));
    int size = 0;
    insert(heap, &size, (Node){source, 0});

    while (size > 0) {
        Node node = extractMin(heap, &size);
        int u = node.vertex;

        if (visited[u]) continue;

        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] > 0 && !visited[v] && dist[v] > dist[u] + graph[u][v]) {
                dist[v] = dist[u] + graph[u][v];
                insert(heap, &size, (Node){v, dist[v]});
            }
        }
    }

    // Print shortest distances
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; i++) {
        printf("%d\t\t%d\n", i, dist[i]);
    }

    free(dist);
    free(visited);
    free(heap);
}

int main() {
    int V = 9;
    int** graph = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        graph[i] = (int*)malloc(V * sizeof(int));
    }

    // Initialize the graph
    graph[0][0] = 0; graph[0][1] = 4; graph[0][2] = 0; graph[0][3] = 0; graph[0][4] = 0; graph[0][5] = 0; graph[0][6] = 0; graph[0][7] = 8; graph[0][8] = 0;
    graph[1][0] = 4; graph[1][1] = 0; graph[1][2] = 8; graph[1][3] = 0; graph[1][4] = 0; graph[1][5] = 0; graph[1][6] = 0; graph[1][7] = 11; graph[1][8] = 0;
    graph[2][0] = 0; graph[2][1] = 8; graph[2][2] = 0; graph[2][3] = 7; graph[2][4] = 0; graph[2][5] = 4; graph[2][6] = 0; graph[2][7] = 0; graph[2][8] = 2;
    graph[3][0] = 0; graph[3][1] = 0; graph[3][2] = 7; graph[3][3] = 0; graph[3][4] = 9; graph[3][5] = 14; graph[3][6] = 0; graph[3][7] = 0; graph[3][8] = 0;
    graph[4][0] = 0; graph[4][1] = 0; graph[4][2] = 0; graph[4][3] = 9; graph[4][4] = 0; graph[4][5] = 10; graph[4][6] = 0; graph[4][7] = 0; graph[4][8] = 0;
    graph[5][0] = 0; graph[5][1] = 0; graph[5][2] = 4; graph[5][3] = 14; graph[5][4] = 10; graph[5][5] = 0; graph[5][6] = 2; graph[5][7] = 0; graph[5][8] = 0;
    graph[6][0] = 0; graph[6][1] = 0; graph[6][2] = 0; graph[6][3] = 0; graph[6][4] = 0; graph[6][5] = 2; graph[6][6] = 0; graph[6][7] = 1; graph[6][8] = 6;
    graph[7][0] = 8; graph[7][1] = 11; graph[7][2] = 0; graph[7][3] = 0; graph[7][4] = 0; graph[7][5] = 0; graph[7][6] = 1; graph[7][7] = 0; graph[7][8] = 7;
    graph[8][0] = 0; graph[8][1] = 0; graph[8][2] = 2; graph[8][3] = 0; graph[8][4] = 0; graph[8][5] = 0; graph[8][6] = 6; graph[8][7] = 7; graph[8][8] = 0;

    dijkstra(graph, V, 0);

    // Free the memory
    for (int i = 0; i < V; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}