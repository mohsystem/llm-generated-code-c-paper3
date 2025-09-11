#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Adjacency list representation of a graph
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

// Create a new node
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Create a graph
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

// Add edge
void addEdge(Graph* graph, int src, int dest) {
    // Add edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Depth-First Search
void DFS(Graph* graph, int startVertex, int* visitedArray, int *visitedCount) {
    if (startVertex >= graph->numVertices || startVertex < 0)
        return;
    graph->visited[startVertex] = true;

    visitedArray[*visitedCount] = startVertex;
    (*visitedCount)++;
    
    Node* temp = graph->adjLists[startVertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!graph->visited[adjVertex]) {
            DFS(graph, adjVertex, visitedArray, visitedCount);
        }
        temp = temp->next;
    }
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
    int visited1[4];
    int visitedCount1 = 0;
    DFS(graph1, 2, visited1, &visitedCount1);
    for (int i = 0; i < visitedCount1; i++) {
        printf("%d ", visited1[i]);
    }
    printf("\n"); // Output: 2 0 1 3

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
    int visited2[5];
    int visitedCount2 = 0;
    DFS(graph2, 0, visited2, &visitedCount2);
    for (int i = 0; i < visitedCount2; i++) {
        printf("%d ", visited2[i]);
    }
    printf("\n"); // Output: 0 1 3 4 2 


    // Test case 3 - Empty Graph
    Graph* graph3 = createGraph(0);
    int visited3[0];
    int visitedCount3 = 0;
    DFS(graph3, 0, visited3, &visitedCount3); // No Output


    // Test case 4 - Single Node
    Graph* graph4 = createGraph(1);
    int visited4[1];
    int visitedCount4 = 0;
    DFS(graph4, 0, visited4, &visitedCount4);
    for (int i = 0; i < visitedCount4; i++) {
        printf("%d ", visited4[i]);
    }
    printf("\n"); // Output: 0

    // Test case 5
    Graph* graph5 = createGraph(5);
    addEdge(graph5, 0, 1);
    addEdge(graph5, 0, 2);
    addEdge(graph5, 1, 3);
    addEdge(graph5, 2, 4);
    int visited5[5];
    int visitedCount5 = 0;
    DFS(graph5, 0, visited5, &visitedCount5);
    for (int i = 0; i < visitedCount5; i++) {
        printf("%d ", visited5[i]);
    }
    printf("\n"); // Output: 0 1 3 2 4

    return 0;
}