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
    bool* visited; // added to track visited nodes
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
    // Comment out these lines for directed graph.
     newNode = createNode(src);
     newNode->next = graph->adjLists[dest];
     graph->adjLists[dest] = newNode;


}

// BFS algorithm
void bfs(Graph* graph, int startVertex) {

     if (graph == NULL || startVertex < 0 || startVertex >= graph->numVertices) {
        return; 
    }

    int* queue = malloc(graph->numVertices * sizeof(int));
    int front = 0, rear = -1;
    
    graph->visited[startVertex] = true;
    queue[++rear] = startVertex;

    while (front <= rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->data;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = true;
                queue[++rear] = adjVertex;
            }
            temp = temp->next;
        }
    }
     free(queue);
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
    bfs(graph1, 2);
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
        bfs(graph2, 1);
        printf("\n");



    // Test case 3: Empty graph
        Graph* graph3 = createGraph(0);
        bfs(graph3, 0); // Should not crash
        printf("\n");



    // Test case 4
        Graph* graph4 = createGraph(3);
        addEdge(graph4, 0, 1);
        addEdge(graph4, 0, 2);
        bfs(graph4, 0);
        printf("\n");

     // Test case 5: Node with no neighbors
        Graph* graph5 = createGraph(1);
        bfs(graph5, 0);
        printf("\n");


    return 0;
}