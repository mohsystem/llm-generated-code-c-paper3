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

    // Add edge from dest to src (for undirected graph)
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}


// Breadth-First Search
void bfs(Graph* graph, int startVertex) {

     if (graph == NULL || startVertex < 0 || startVertex >= graph->numVertices) {
        return; // Invalid input, handle gracefully.
    }

    int *visited = (int *)malloc(graph->numVertices * sizeof(int));
    for(int i = 0; i< graph->numVertices; i++)
        visited[i] = 0;


    int *queue = (int*)malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = -1;
    
    visited[startVertex] = 1;
    queue[++rear] = startVertex;


    printf("BFS traversal starting from vertex %d: ", startVertex);
    while (front <= rear)
    {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);
        Node *temp = graph->adjLists[currentVertex];

        while (temp) {
            int adjVertex = temp->data;
            if (visited[adjVertex] == 0) {
                visited[adjVertex] = 1;
                queue[++rear] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
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
    bfs(graph1, 2); // Expected: 2 0 3 1
    

    Graph *graph2 = createGraph(5);
    addEdge(graph2, 0, 1);
    addEdge(graph2, 0, 2);
    addEdge(graph2, 1, 0);
    addEdge(graph2, 1, 3);
    addEdge(graph2, 1, 4);
    addEdge(graph2, 2, 0);
    addEdge(graph2, 3, 1);
    addEdge(graph2, 4, 1);
    bfs(graph2, 0); // Expected: 0 1 2 3 4

    Graph *graph3 = createGraph(1);
    bfs(graph3, 0); // Expected: 0

    Graph *graph4 = createGraph(3);
    addEdge(graph4, 0, 1);
    addEdge(graph4, 0, 2);
    bfs(graph4, 0); // Expected: 0 1 2

    Graph *graph5 = createGraph(7);
    addEdge(graph5, 0, 1);
    addEdge(graph5, 0, 2);
    addEdge(graph5, 0, 3);
    addEdge(graph5, 1, 4);
    addEdge(graph5, 2, 5);
    addEdge(graph5, 3, 6);
    bfs(graph5, 0); // Expected: 0 1 2 3 4 5 6



    return 0;
}