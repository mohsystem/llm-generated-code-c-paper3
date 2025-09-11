#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
    int* visited;
} Graph;

Node* createNode(int vertex) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void DFS(Graph* graph, int vertex) {
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == 0) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

int main() {
    Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 3);

    printf("Starting DFS from vertex 2:\n");
    DFS(graph, 2); // Test case 1
    printf("\n");

    // Resetting visited array
    for (int i = 0; i < 4; i++) graph->visited[i] = 0;

    printf("Starting DFS from vertex 0:\n");
    DFS(graph, 0); // Test case 2
    printf("\n");

    // Resetting visited array
    for (int i = 0; i < 4; i++) graph->visited[i] = 0;

    printf("Starting DFS from vertex 1:\n");
    DFS(graph, 1); // Test case 3
    printf("\n");

    // Resetting visited array
    for (int i = 0; i < 4; i++) graph->visited[i] = 0;

    printf("Starting DFS from vertex 3:\n");
    DFS(graph, 3); // Test case 4
    printf("\n");

    // Resetting visited array
    for (int i = 0; i < 4; i++) graph->visited[i] = 0;

    printf("Starting DFS from vertex 4 (not connected):\n");
    DFS(graph, 4); // Test case 5
    printf("\n");

    return 0;
}