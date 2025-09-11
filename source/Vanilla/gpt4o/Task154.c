#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjLists;
    int* visited;
};

struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

void dfsUtil(struct Graph* graph, int vertex) {
    struct Node* adjList = graph->adjLists[vertex];
    struct Node* temp = adjList;

    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (graph->visited[connectedVertex] == 0) {
            dfsUtil(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void DFS(struct Graph* graph, int startVertex) {
    dfsUtil(graph, startVertex);
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->visited[i] == 0) {
            dfsUtil(graph, i);
        }
    }
}

int main() {
    struct Graph* graph = createGraph(5);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);

    printf("DFS starting from vertex 0:\n");
    DFS(graph, 0);
    printf("\n");

    for (int i = 0; i < 5; i++) {
        graph->visited[i] = 0;
    }

    printf("DFS starting from vertex 1:\n");
    DFS(graph, 1);
    printf("\n");

    for (int i = 0; i < 5; i++) {
        graph->visited[i] = 0;
    }

    printf("DFS starting from vertex 2:\n");
    DFS(graph, 2);
    printf("\n");

    for (int i = 0; i < 5; i++) {
        graph->visited[i] = 0;
    }

    printf("DFS starting from vertex 3:\n");
    DFS(graph, 3);
    printf("\n");

    for (int i = 0; i < 5; i++) {
        graph->visited[i] = 0;
    }

    printf("DFS starting from vertex 4:\n");
    DFS(graph, 4);
    printf("\n");

    return 0;
}