#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjLists[MAX_NODES];
    bool visited[MAX_NODES];
} Graph;

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph() {
    Graph* graph = malloc(sizeof(Graph));
    for (int i = 0; i < MAX_NODES; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
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

    graph->visited[vertex] = true;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}


int main() {
    Graph* graph1 = createGraph();
    addEdge(graph1, 0, 1);
    addEdge(graph1, 0, 2);
    addEdge(graph1, 1, 2);
    addEdge(graph1, 2, 0);
    addEdge(graph1, 2, 3);
    addEdge(graph1, 3, 3);
    DFS(graph1, 2);
    printf("\n");

    Graph* graph2 = createGraph();
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

        Graph* graph3 = createGraph();
    DFS(graph3, 0);
    printf("\n");


    Graph* graph4 = createGraph();
    DFS(graph4, 0);
    printf("\n");


    Graph* graph5 = createGraph();
    addEdge(graph5, 0, 1);
    addEdge(graph5, 0, 2);
    addEdge(graph5, 0, 3);
    addEdge(graph5, 1, 0);
    addEdge(graph5, 1, 4);
    addEdge(graph5, 2, 0);
    addEdge(graph5, 2, 5);
    addEdge(graph5, 3, 0);
    addEdge(graph5, 3, 6);
    addEdge(graph5, 4, 1);
    addEdge(graph5, 5, 2);
    addEdge(graph5, 6, 3);

    DFS(graph5, 0);
    printf("\n");


    return 0;
}