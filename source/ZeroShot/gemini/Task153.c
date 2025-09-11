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


// Create a new node
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = v;
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

// BFS algorithm
void bfs(Graph* graph, int startVertex) {
    // Create a queue for BFS
    int* queue = malloc(graph->numVertices * sizeof(int));
    int front = -1, rear = -1;


    // Mark the current node as visited and enqueue it
    graph->visited[startVertex] = true;
    queue[++rear] = startVertex;
    printf("%d ", startVertex);
    while (front != rear)
    {
        // Dequeue a vertex from queue and print it
        int currentVertex = queue[++front];


        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited and enqueue it
        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->data;
            if (!graph->visited[adjVertex]) {
                printf("%d ", adjVertex);

                graph->visited[adjVertex] = true;
                queue[++rear] = adjVertex;

            }
            temp = temp->next;
        }
    }
    free(queue);
}
int main() {
    // Test cases are difficult to implement due to the graph structure needing to be manually initialized in C.
    // Demonstrating basic functionality.

     Graph* graph = createGraph(4);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 3);
    bfs(graph, 2); // Example usage
    printf("\n");

    Graph* graph2 = createGraph(6);
    addEdge(graph2, 1, 2);
    addEdge(graph2, 1, 3);
    addEdge(graph2, 2, 4);
    addEdge(graph2, 2, 5);
    bfs(graph2, 1); // Example usage
    printf("\n");



    return 0;
}