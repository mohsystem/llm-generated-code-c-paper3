
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_VERTICES 100

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Graph {
    struct Node* adjacencyList[MAX_VERTICES];
    int vertices;
};

struct Node* createNode(int vertex, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->vertex = vertex;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    if (vertices <= 0 || vertices > MAX_VERTICES) {
        return NULL;
    }

    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    if (graph == NULL) {
        return NULL;
    }

    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjacencyList[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int source, int destination, int weight) {
    if (graph == NULL || source < 0 || destination < 0 || 
        source >= graph->vertices || destination >= graph->vertices) {
        return;
    }

    struct Node* newNode = createNode(destination, weight);
    if (newNode == NULL) {
        return;
    }
    newNode->next = graph->adjacencyList[source];
    graph->adjacencyList[source] = newNode;

    // For undirected graph
    newNode = createNode(source, weight);
    if (newNode == NULL) {
        return;
    }
    newNode->next = graph->adjacencyList[destination];
    graph->adjacencyList[destination] = newNode;
}

int minDistance(int distances[], bool visited[], int vertices) {
    int min = INT_MAX;
    int minIndex = -1;

    for (int v = 0; v < vertices; v++) {
        if (!visited[v] && distances[v] < min) {
            min = distances[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void dijkstra(struct Graph* graph, int startNode, int distances[]) {
    if (graph == NULL || startNode < 0 || startNode >= graph->vertices) {
        return;
    }

    bool* visited = (bool*)calloc(graph->vertices, sizeof(bool));
    if (visited == NULL) {
        return;
    }

    for (int i = 0; i < graph->vertices; i++) {
        distances[i] = INT_MAX;
    }
    distances[startNode] = 0;

    for (int count = 0; count < graph->vertices - 1; count++) {
        int u = minDistance(distances, visited, graph->vertices);
        if (u == -1) break;
        
        visited[u] = true;
        struct Node* temp = graph->adjacencyList[u];
        
        while (temp != NULL) {
            int v = temp->vertex;
            if (!visited[v] && distances[u] != INT_MAX && 
                distances[u] + temp->weight < distances[v]) {
                distances[v] = distances[u] + temp->weight;
            }
            temp = temp->next;
        }
    }
    free(visited);
}

void freeGraph(struct Graph* graph) {
    if (graph == NULL) {
        return;
    }

    for (int i = 0; i < graph->vertices; i++) {
        struct Node* current = graph->adjacencyList[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph);
}

void printResult(int distances[], int vertices) {
    printf("[");
    for (int i = 0; i < vertices; i++) {
        if', type='text')