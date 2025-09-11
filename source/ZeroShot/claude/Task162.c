
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_NODES 1000

struct Edge {
    int dest;
    int weight;
};

struct Graph {
    struct Edge* edges[MAX_NODES];
    int edge_count[MAX_NODES];
    int n;
};

int* dijkstra(struct Graph* graph, int start) {
    int* distances = (int*)malloc(graph->n * sizeof(int));
    bool* visited = (bool*)calloc(graph->n, sizeof(bool));
    
    for (int i = 0; i < graph->n; i++) {
        distances[i] = INT_MAX;
    }
    distances[start] = 0;

    for (int count = 0; count < graph->n - 1; count++) {
        int min = INT_MAX;
        int min_index = -1;

        for (int v = 0; v < graph->n; v++) {
            if (!visited[v] && distances[v] <= min) {
                min = distances[v];
                min_index = v;
            }
        }

        if (min_index == -1) break;
        visited[min_index] = true;

        for (int i = 0; i < graph->edge_count[min_index]; i++) {
            int v = graph->edges[min_index][i].dest;
            int weight = graph->edges[min_index][i].weight;

            if (!visited[v] && distances[min_index] != INT_MAX && 
                distances[min_index] + weight < distances[v]) {
                distances[v] = distances[min_index] + weight;
            }
        }
    }

    free(visited);
    return distances;
}

struct Graph* createGraph(int n) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->n = n;
    for (int i = 0; i < n; i++) {
        graph->edge_count[i] = 0;
        graph->edges[i] = (struct Edge*)malloc(MAX_NODES * sizeof(struct Edge));
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest, int weight) {
    graph->edges[src][graph->edge_count[src]].dest = dest;
    graph->edges[src][graph->edge_count[src]].weight = weight;
    graph->edge_count[src]++;
}

void freeGraph(struct Graph* graph) {
    for (int i = 0; i < graph->n; i++) {
        free(graph->edges[i]);
    }
    free(graph);
}

int main() {
    // Test Case 1: Simple graph
    struct Graph* graph1 = createGraph(4);
    addEdge(graph1, 0, 1, 1);
    addEdge(graph1, 0, 2, 4);
    addEdge(graph1, 1, 2, 2);
    addEdge(graph1, 1, 3, 5);
    addEdge(graph1, 2, 3, 1);
    
    int* result1 = dijkstra(graph1, 0);
    printf("Test 1: ");
    for (int i = 0; i < graph1->n; i++) {
        printf("%d ", result1[i]);
    }
    printf("\\n");
    free(result1);
    freeGraph(graph1);

    // Test Case 2: Linear graph
    struct Graph* graph2 = createGraph(3);
    addEdge(graph2, 0, 1, 1);
    addEdge(graph2, 1, 2, 2);
    
    int* result2 = dijkstra(graph2, 0);
    printf("Test 2: ");
    for (int i = 0; i < graph2->n; i++) {
        printf("%d ", result2[i]);
    }
    printf("\\n");
    free(result2);
    freeGraph(graph2);

    // Test Case 3: Cyclic graph
    struct Graph* graph3 = createGraph(3);
    addEdge(graph3, 0, 1, 1);
    addEdge(graph3, 1, 2, 2);
    addEdge(graph3, 2, 0, 3);
    
    int* result3 = dijkstra(graph3, 0);
    printf("Test 3: ");
    for (int i = 0; i < graph3->n; i++) {
        printf("%d ", result3[i]);
    }
    printf("\\n");
    free(result3);
    freeGraph(graph3);

    // Test Case 4: Disconnected graph
    struct Graph* graph4 = createGraph(4);
    addEdge(graph4, 0, 1, 1);
    addEdge(graph4, 2, 3, 1);
    
    int* result4 = dijkstra(graph4, 0);
    printf("Test 4: ");
    for (int i = 0; i < graph4->n; i++) {
        printf("%d ", result4[i]);
    }
    printf("\\n");
    free(result4);
    freeGraph(graph4);

    // Test Case 5: Single node
    struct Graph* graph5 = createGraph(1);
    
    int* result5 = dijkstra(graph5, 0);
    printf("Test 5: ");
    for (int i = 0; i < graph5->n; i++) {
        printf("%d ", result5[i]);
    }
    printf("\\n");
    free(result5);
    freeGraph(graph5);

    return 0;
}
