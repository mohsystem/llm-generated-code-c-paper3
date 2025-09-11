#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Adjacency list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Adjacency list representation of graph
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;

// Create a new node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with 'numVertices' vertices
Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjLists = (Node**)malloc(numVertices * sizeof(Node*));
    graph->visited = (bool*)malloc(numVertices * sizeof(bool));
    for (int i = 0; i < numVertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

// Add edge from 'src' to 'dest'
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
}

// Breadth-First Search algorithm
void bfs(Graph* graph, int startVertex) {
    // Handle cases where startVertex is out of bounds
    if (startVertex < 0 || startVertex >= graph->numVertices) {
        return;
    }

    int* queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = 0;
    queue[rear++] = startVertex;
    graph->visited[startVertex] = true;


    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);
        
        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->data;
            if (!graph->visited[adjVertex]) {
                queue[rear++] = adjVertex;
                graph->visited[adjVertex] = true;
            }
            temp = temp->next;
        }
    }
    printf("\n");
    free(queue); // Free allocated memory
}


int main() {
    // Test cases
     Graph* graph1 = createGraph(4);
    addEdge(graph1, 0, 1);
    addEdge(graph1, 0, 2);
    addEdge(graph1, 1, 2);
    addEdge(graph1, 2, 0);
    addEdge(graph1, 2, 3);
    addEdge(graph1, 3, 3);
    bfs(graph1, 2);


    Graph* graph2 = createGraph(6);
    addEdge(graph2, 1, 2);
    addEdge(graph2, 1, 3);
    addEdge(graph2, 2, 4);
    addEdge(graph2, 2, 5);
    bfs(graph2, 1);


    Graph* graph3 = createGraph(1);
    bfs(graph3, 0);

    Graph* graph4 = createGraph(1);
    bfs(graph4, 0);


    Graph* graph5 = createGraph(4);
    addEdge(graph5, 0, 1);
    addEdge(graph5, 0, 2);
    addEdge(graph5, 1, 0);
    addEdge(graph5, 2, 0);
    addEdge(graph5, 2, 3);
    bfs(graph5, 0);


    return 0;
}