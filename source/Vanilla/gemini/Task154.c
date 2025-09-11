#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Adjacency list
typedef struct Graph {
    int numVertices;
    Node** adjLists;
    bool* visited;
} Graph;


// Create a node
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

// DFS algorithm
void DFS(Graph* graph, int vertex, int* visited_nodes, int *visited_count) {
    Node* adjList = graph->adjLists[vertex];
    Node* temp = adjList;

    graph->visited[vertex] = true;
    visited_nodes[*visited_count] = vertex;
    (*visited_count)++;
    //printf("Visited %d \n", vertex);

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (graph->visited[connectedVertex] == false) {
            DFS(graph, connectedVertex, visited_nodes, visited_count);
        }
        temp = temp->next;
    }
}


int main() {
     // Test cases are implemented within the main function
     // because creating dynamic graphs for each test case 
     // with separate functions requires a more complex implementation
     // for memory management and passing dynamic structures between functions.

    // Test case 1
    Graph* graph1 = createGraph(4);
    addEdge(graph1, 0, 1);
    addEdge(graph1, 0, 2);
    addEdge(graph1, 1, 2);
    addEdge(graph1, 2, 0);
    addEdge(graph1, 2, 3);
    addEdge(graph1, 3, 3);
    int visited_nodes1[4]; int visited_count1 = 0;
    DFS(graph1, 2, visited_nodes1, &visited_count1);
    for(int i = 0; i < visited_count1; ++i) printf("%d ", visited_nodes1[i]);
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
    int visited_nodes2[5]; int visited_count2 = 0;
    DFS(graph2, 0, visited_nodes2, &visited_count2);
    for(int i = 0; i < visited_count2; ++i) printf("%d ", visited_nodes2[i]);
    printf("\n");


    // Test case 3: Empty graph
    Graph* graph3 = createGraph(1);
    int visited_nodes3[1]; int visited_count3 = 0;
    DFS(graph3, 0, visited_nodes3, &visited_count3); // Start from node 0 (even though it's empty)
    for(int i = 0; i < visited_count3; ++i) printf("%d ", visited_nodes3[i]);
    printf("\n");


    // Test case 4
    Graph* graph4 = createGraph(2);
    addEdge(graph4, 0, 1);
    int visited_nodes4[2]; int visited_count4 = 0;
    DFS(graph4, 0, visited_nodes4, &visited_count4);
    for(int i = 0; i < visited_count4; ++i) printf("%d ", visited_nodes4[i]);
    printf("\n");



    // Test case 5
    Graph* graph5 = createGraph(7);
    addEdge(graph5, 0, 1);
    addEdge(graph5, 0, 2);
    addEdge(graph5, 0, 3);
    addEdge(graph5, 1, 4);
    addEdge(graph5, 2, 5);
    addEdge(graph5, 3, 6);
    int visited_nodes5[7]; int visited_count5 = 0;
    DFS(graph5, 0, visited_nodes5, &visited_count5);
    for(int i = 0; i < visited_count5; ++i) printf("%d ", visited_nodes5[i]);
    printf("\n");



    return 0;
}