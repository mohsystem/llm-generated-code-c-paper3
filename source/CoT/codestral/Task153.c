#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 5

struct Node {
    int vertex;
    struct Node* next;
};

struct Node* createNode(int);

struct Graph {
    int numVertices;
    struct Node** adjList;
    bool* visited;
};

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjList = malloc(vertices * sizeof(struct Node*));
    graph->visited = malloc(vertices * sizeof(bool));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = false;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

void breadthFirstSearch(struct Graph* graph, int startVertex) {
    struct Node* temp;
    int currentVertex;
    struct Node* queue[MAX_VERTICES];
    int front = -1, rear = -1;

    graph->visited[startVertex] = true;
    printf("%d ", startVertex);

    queue[++rear] = createNode(startVertex);

    while (front != rear) {
        currentVertex = queue[++front]->vertex;

        temp = graph->adjList[currentVertex];

        while (temp) {
            int adjVertex = temp->vertex;

            if (graph->visited[adjVertex] == false) {
                graph->visited[adjVertex] = true;
                printf("%d ", adjVertex);
                queue[++rear] = createNode(adjVertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    struct Graph* graph = createGraph(MAX_VERTICES);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);

    breadthFirstSearch(graph, 2);

    return 0;
}