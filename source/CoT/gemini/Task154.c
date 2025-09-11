#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Adjacency list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Adjacency list representation of a graph
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;


// Depth-First Search
void DFS(Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->data;
        if (!graph->visited[adjVertex]) {
            DFS(graph, adjVertex);
        }
        temp = temp->next;
    }
}


//  Helper function to create a new node
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

// Helper function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(bool));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}

// Helper function to add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

int main() {
     // Test case 1
    Graph* graph1 = createGraph(4);
    addEdge(graph1, 0, 1);
    addEdge(graph1, 0, 2);
    addEdge(graph1, 1, 2);
    addEdge(graph1, 2, 0);
    addEdge(graph1, 2, 3);
    addEdge(graph1, 3, 3);
    DFS(graph1, 2);
    printf("\n");


    // Test case 2
    Graph* graph2 = createGraph(5);
    addEdge(graph2, 0, 1);
    addEdge(graph2, 0, 2);
    addEdge(graph2, 1, 0);
    addEdge(graph2, 1, 3);
    addEdge(graph2, 1, 4);
    addEdge(graph2, 2, 0);
    addEdge(graph2, 3, 1);
    addEdge(graph2, 4, 1);
    DFS(graph2, 0);
    printf("\n");

    // Test case 3 - Empty graph
    Graph* graph3 = createGraph(1);
    DFS(graph3, 0);
    printf("\n");


    // Test case 4
    Graph* graph4 = createGraph(4);
    addEdge(graph4, 0, 1);
    addEdge(graph4, 0, 2);
    addEdge(graph4, 0, 3);

    DFS(graph4, 0);
    printf("\n");

    // Test case 5 - Single node graph
    Graph* graph5 = createGraph(1);
    DFS(graph5, 0);
    printf("\n");

    return 0;
}